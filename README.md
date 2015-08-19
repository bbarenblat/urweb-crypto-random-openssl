urweb-crypto-random-openssl
===========================

urweb-crypto-random-openssl provides cryptographically secure random byte and
blob generation facilities using [OpenSSL][].

**This library requires Ur/Web 20150819 or later.**  If you use an earlier
version, you _will_ fall afoul of [bug 206][], and you _will_ introduce a
potentially security-relevant race condition in your application.

Installation
------------

The standard

    autoreconf -vis
    ./configure
    make
    make install

dance should work properly.

License
-------

urweb-crypto-random-openssl is licensed under the [Apache License, Version 2.0][].


[Apache License, Version 2.0]: https://www.apache.org/licenses/LICENSE-2.0
[bug 206]: http://www.impredicative.com/mantis/view.php?id=206 "Ur/Web bug #206: Linking FFI libraries which use OpenSSL introduces race condition"
[OpenSSL]: https://openssl.org/


<!-- Local Variables: -->
<!-- mode: markdown -->
<!-- End: -->
