/*
 * Copyright (C) ARM Limited 1999. All rights reserved.
 */

struct NullApp {
    char special[16];
    unsigned offset;
};

struct NullApp const null_application = {
    "*** Service ***", 0
};

