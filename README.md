
node-syslog
===========

> Syslog-ng TCP client for node, with basic fault-tolerance.

installation
------------

    $ npm install syslog

synopsis
--------
    
    var syslog = require('syslog');
    var logger = syslog.createClient(514, 'localhost');

    logger.info("ping!");

log levels
----------

In increasing order of severity:

- debug
- info
- notice
- warning
- error
- crit
- alert
- emerg

These are available as methods on Client, ex: `logger.crit()`.

You may also call the `log` method, and pass the level as the 2nd argument:

    logger.log('fnord!', syslog.LOG_CRIT);

The default level is `info`.

configuration
-------------

You will have to configure your syslog server to accept TCP connections.
This is usually done in `/etc/syslog-ng.conf`. Let's say you have an app called `fnord`,
the configuration would look something like this:

    source tcp_s {
      tcp(ip(0.0.0.0) port(514) max-connections(256));
    };
    destination fnord_d {
      file("/var/log/fnord.log");
    };
    log { source(tcp_s); destination(fnord_d); };

If you have multiple apps which need to log via TCP, you can specify filters, as such:

    filter fnord_f { program("fnord"); };

Then modify the log statement to read:

    log { source(tcp_s); filter(fnord_f); destination(fnord_d); };

Now if you have another app, called `bnord`, create similar `destination` and `filter` configurations for it,
and specify a new log statement, with the same `source`:

    log { source(tcp_s); filter(bnord_f); destination(bnord_d); };

For this to work, you have to make sure you set the `process.title` variable in your node app.

    process.title = 'fnord';

Alternatively, you can pass it as an option to `createClient`:

    syslog.createClient(514, 'localhost', { name: 'fnord' });

license
-------

See `LICENSE` file.

> Copyright (c) 2011 Alexis Sellier

