#pragma once

#define SUGAR_CONCAT(a, b) SUGAR_CONCAT_PRIMITIVE(a, b)
#define SUGAR_CONCAT_PRIMITIVE(a, b) a##b

#define SUGAR_NOOP \
    do {           \
    } while (false)
