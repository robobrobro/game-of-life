#include "config.h"

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <yaml.h>
#include "log.h"

#define LOG_YAML_ERROR(msg, error) \
    switch (error) { \
        case YAML_MEMORY_ERROR: \
            LOG_ERROR(msg ": could not allocate or reallocate a block of memory"); \
            break; \
        case YAML_READER_ERROR: \
            LOG_ERROR(msg ": could not read or decode the input stream"); \
            break; \
        case YAML_SCANNER_ERROR: \
            LOG_ERROR(msg ": could not scan the input stream"); \
            break; \
        case YAML_PARSER_ERROR: \
            LOG_ERROR(msg ": could not parse the input stream"); \
            break; \
        case YAML_COMPOSER_ERROR: \
            LOG_ERROR(msg ": could not compose a YAML document"); \
            break; \
        case YAML_WRITER_ERROR: \
            LOG_ERROR(msg ": could not write to the output stream"); \
            break; \
        case YAML_EMITTER_ERROR: \
            LOG_ERROR(msg ": could not emit a YAML stream"); \
            break; \
        default: \
            LOG_ERROR(msg ": unknown error"); \
            break; \
    } \

bool
config_parse(const char *path, config_parse_cb_t cb, void *ctx)
{
    bool succeeded = false;
    FILE *file;
    yaml_parser_t parser;
    yaml_document_t doc;
    yaml_node_t *node;
    int node_idx;

    assert(path != NULL);
    assert(cb != NULL);

    file = fopen(path, "rb");
    if (!file) {
        LOG_ERROR("failed to open file: %s", strerror(errno));
        return false;
    }

    if (!yaml_parser_initialize(&parser)) {
        LOG_ERROR("failed to initialize YAML parser");
        goto exit;
    }

    yaml_parser_set_input_file(&parser, file);

    if (!yaml_parser_load(&parser, &doc)) {
        LOG_YAML_ERROR("failed to parse YAML file", parser.error);
        goto exit;
    }

    node_idx = 1;
    node = yaml_document_get_node(&doc, node_idx);

    while (node) {
        yaml_node_pair_t *pair;
        const char *key;
        const char *value;
        int action;

        if (node->type != YAML_MAPPING_NODE) {
            LOG_ERROR("unsupported YAML node type: %d", node->type);
            node = yaml_document_get_node(&doc, ++node_idx);
            continue;
        }

        pair = node->data.mapping.pairs.start;
        while (pair && pair != node->data.mapping.pairs.end) {
            yaml_node_t *key_node = yaml_document_get_node(&doc, pair->key);
            yaml_node_t *value_node = yaml_document_get_node(&doc, pair->value);

            if (!key_node || !value_node) {
                pair++;
                continue;
            }
            
            key = (typeof(key))key_node->data.scalar.value;
            value = (typeof(value))value_node->data.scalar.value;

            action = cb(key, value, ctx);
            switch (action) {
                case CONFIG_PARSE_CONTINUE:
                    node_idx = pair->value + 1;
                    pair++;
                    break;
                case CONFIG_PARSE_STOP:
                    node_idx = 0;
                    pair = NULL;
                    break;
                case CONFIG_PARSE_RESTART:
                    node_idx = 1;
                    pair = NULL;
                    break;
                default:
                    LOG_ERROR("invalid parser action: %d", action);
                    break;
            }
        }

        node = yaml_document_get_node(&doc, node_idx);
    }

    yaml_document_delete(&doc);
    succeeded = true;

exit:
    fclose(file);
    yaml_parser_delete(&parser);
    return succeeded;
}
