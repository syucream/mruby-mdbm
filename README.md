# mruby-mdbm

mruby binding of [yahoo/mdbm](https://github.com/yahoo/mdbm)

# Quickstart

1. build mruby with mruby-mdbm

```
# mruby root dir
$ MRUBY_CONFIG=./path/to/build_config.rb ./minirake
```

2. Run mirb and test MDBM class

```
$ ./build/host/bin/mirb
mirb - Embeddable Interactive Ruby Shell

> mdbm = MDBM.new('/tmp/tmp.mdbm', 0666, MDBM::MDBM_O_RDWR | MDBM::MDBM_O_CREAT)
 => #<MDBM:0x7ff6d4803b50>
> mdbm.store('key', 'value')
 => nil
> mdbm.fetch('key')
 => "value"
> mdbm.store('key', 'new value')
 => nil
> mdbm.fetch('key')
 => "new value"
> mdbm['key2'] = 'value2'
 => "value2"
> mdbm['key2']
 => "value2"
> mdbm.close
 => nil
```

# License

MITL
