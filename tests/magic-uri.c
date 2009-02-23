/*
 Copyright (C) 2008 Christian Dywan <christian@twotoasts.de>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 See the file COPYING for the full license text.
*/

#if HAVE_CONFIG_H
    #include <config.h>
#endif

#include "compat.h"
#include "sokoke.h"

int
main (int    argc,
      char** argv)
{
    KatzeArray* search_engines;
    KatzeItem* item;
    gchar* uri;
    gchar* a, *b;

    gtk_init_check (&argc, &argv);

    search_engines = katze_array_new (KATZE_TYPE_ITEM);
    item = g_object_new (KATZE_TYPE_ITEM,
                         "uri", "http://www.searchmash.com/search/%s",
                         "token", "sm", NULL);
    katze_array_add_item (search_engines, item);
    g_object_unref (item);
    item = g_object_new (KATZE_TYPE_ITEM,
                         "uri", "http://www.searchmash.com/search/",
                         "token", "se", NULL);
    katze_array_add_item (search_engines, item);
    g_object_unref (item);

#define test_input(input, expected) \
  uri = sokoke_magic_uri (input, search_engines); \
  if (g_strcmp0 (uri, expected)) \
    { \
      g_print ("Input: %s\nExpected: %s\nResult: %s\n\n", \
               input ? input : "NULL", \
               expected ? expected : "NULL", \
               uri ? uri : "NULL"); \
      return 1; \
    } \
  g_free (uri)
#define SM "http://www.searchmash.com/search/"

    test_input ("ftp://ftp.mozilla.org", "ftp://ftp.mozilla.org");
    test_input ("ftp://ftp.mozilla.org/pub", "ftp://ftp.mozilla.org/pub");
    test_input ("http://www.example.com", "http://www.example.com");
    test_input ("http://example.com", "http://example.com");
    test_input ("example.com", "http://example.com");
    test_input ("example.com", "http://example.com");
    test_input ("/home/user/midori.html", "file:///home/user/midori.html");
    a = g_get_current_dir ();
    b = g_strconcat ("file://", a, G_DIR_SEPARATOR_S, "magic-uri.c", NULL);
    g_free (a);
    test_input ("magic-uri.c", b);
    g_free (b);
    test_input ("localhost", "http://localhost");
    test_input ("localhost:8000", "http://localhost:8000");
    test_input ("localhost/rss", "http://localhost/rss");
    test_input ("192.168.1.1", "http://192.168.1.1");
    test_input ("192.168.1.1:8000", "http://192.168.1.1:8000");
    test_input ("sm midori", SM "midori");
    test_input ("sm cats dogs", SM "cats dogs");
    test_input ("se cats dogs", SM "cats dogs");
    test_input ("dict midori", NULL);
    test_input ("cats", NULL);
    test_input ("cats dogs", NULL);
    test_input ("gtk 2.0", NULL);
    test_input ("gtk2.0", NULL);
    test_input ("midori0.1.0", NULL);
    test_input ("midori 0.1.0", NULL);
    test_input ("search:cats", NULL);
    test_input ("search:twotoasts.de", NULL);
    test_input ("g cache:127.0.0.1", NULL);
    test_input ("g cache:127.0.0.1/foo", NULL);
    test_input ("g cache:twotoasts.de/foo", NULL);
    test_input ("sm cache:127.0.0.1", SM "cache:127.0.0.1");
    test_input ("sm cache:127.0.0.1/foo", SM "cache:127.0.0.1/foo");
    test_input ("sm cache:twotoasts.de/foo", SM "cache:twotoasts.de/foo");
    test_input ("de.po verbose", NULL);
    test_input ("verbose de.po", NULL);
    test_input ("g de.po verbose", NULL);
    test_input ("sm de.po verbose", SM "de.po verbose");
    test_input ("javascript:alert(1)", "javascript:alert(1)");
    test_input ("sm warning: configure /dev/net: virtual",
                SM "warning: configure /dev/net: virtual");
    #if HAVE_LIBIDN
    test_input ("http://www.münchhausen.at", "http://www.xn--mnchhausen-9db.at");
    test_input ("http://www.خداوند.com/", "http://www.xn--mgbndb8il.com/");
    test_input ("айкидо.com", "http://xn--80aildf0a.com");
    test_input ("http://東京理科大学.jp", "http://xn--1lq68wkwbj6ugkpigi.jp");
    test_input ("https://青のネコ",  "https://xn--u9jthzcs263c");
    #else
    test_input ("http://www.münchhausen.at", "http://www.münchhausen.at");
    test_input ("http://www.خداوند.com/", "http://www.خداوند.com/");
    test_input ("айкидо.com", "http://айкидо.com");
    test_input ("http://東京理科大学.jp", "http://東京理科大学.jp");
    test_input ("https://青のネコ.co.jp",  "https://青のネコ.co.jp");
    #endif
    test_input ("http://en.wikipedia.org/wiki/Kölsch_language",
                "http://en.wikipedia.org/wiki/Kölsch_language");
    test_input ("en.wikipedia.org/wiki/Kölsch_language",
                "http://en.wikipedia.org/wiki/Kölsch_language");
    test_input ("sm Küchenzubehör", SM "Küchenzubehör");
    test_input ("sm 東京理科大学", SM "東京理科大学");

    return 0;
}
