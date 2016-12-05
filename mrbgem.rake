MRuby::Gem::Specification.new('mruby-mdbm') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Ryo Okubo'
  spec.version = '0.0.1'

  mdbm_dir = "#{build_dir}/mdbm"

  if !File.exists?(mdbm_dir)
    Dir.chdir(build_dir) do
      `git submodule init && git submodule update`
    end
  end

  if !File.exists?("#{mdbm_dir}/src/lib/libmdbm.a")
    Dir.chdir(build_dir) do
      `autoreconf -if`
      `make mdbm`
    end
  end

  spec.cc.include_paths << "#{mdbm_dir}/include"
  spec.linker.flags_before_libraries << "#{mdbm_dir}/src/lib/libmdbm.a"
end
