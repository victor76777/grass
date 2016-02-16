# -*- mode: ruby -*-
# vi: set ft=ruby :

### Inspired by https://svn.osgeo.org/gdal/trunk/gdal/Vagrantfile

require 'socket'

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  
  vm_ram = ENV['VAGRANT_VM_RAM'] || 1024
  vm_cpu = ENV['VAGRANT_VM_CPU'] || 2
  
  config.vm.box = "precise64"
  
  config.vm.hostname = "grass-gis-vagrant"
  config.vm.box_url = "http://files.vagrantup.com/precise64.box"
  config.vm.define "grass-gis-vagrant" do |host|
    
    config.vm.network :forwarded_port, guest: 80, host: 8080
    
    host.vm.provider :virtualbox do |vb|
      vb.customize ["modifyvm", :id, "--memory", vm_ram]
      vb.customize ["modifyvm", :id, "--cpus", vm_cpu]
      vb.customize ["modifyvm", :id, "--ioapic", "on"]
      vb.name = "grass-gis-vagrant"
    end  

    config.ssh.forward_agent = true
    config.ssh.forward_x11 = true
    
    ppaRepos = [
      "ppa:ubuntugis/ubuntugis-unstable"
    ]
    
    packageList = [
      "autoconf2.13",
      "autotools-dev",
      "make",
      "g++",
      "gettext",
      "flex",
      "bison",
      "lesstif2-dev",
      "libcairo2-dev",
      "libfftw3-dev",
      "libfreetype6-dev",
      "libgdal-dev",
      "libgeos-dev",
      "libglu1-mesa-dev",
      "libjpeg-dev",
      "libpng-dev",
      "libtiff-dev",
      "libmysqlclient-dev",
      "libncurses5-dev",
      "libpq-dev",
      "libproj-dev",
      "proj-bin",
      "libreadline-dev",
      "libsqlite3-dev",
      "libwxgtk2.8-dev",
      "libxmu-dev",
      "python",
      "python-wxgtk2.8",
      "python-dev",
      "python-numpy",
      "python-ply",
      #    "python-pil",
      "libnetcdf-dev",
      "netcdf-bin",
      "libblas-dev",
      "liblapack-dev",
      "unixodbc-dev",
      "zlib1g-dev"
      #    "liblas",
      #    "liblas-c-dev"
    ]
    
    unless File.exists?(".no_apt_cache")
      cache_dir = "apt-cache/#{config.vm.box}"
      FileUtils.mkdir_p(cache_dir) unless Dir.exists?(cache_dir)
      host.vm.synced_folder cache_dir, "/var/cache/apt/archives"
    end
    
    if Dir.glob("#{File.dirname(__FILE__)}/.vagrant/machines/grass-gis-vagrant/*/id").empty?
      pkg_cmd = "sed -i 's#deb http://us.archive.ubuntu.com/ubuntu/#deb mirror://mirrors.ubuntu.com/mirrors.txt#' /etc/apt/sources.list; "
      
      pkg_cmd << "apt-get update -qq; apt-get install -q -y python-software-properties; "
      
      if ppaRepos.length > 0
	ppaRepos.each { |repo| pkg_cmd << "add-apt-repository -y " << repo << " ; " }
	pkg_cmd << "apt-get update -qq; "
      end
      
      # install packages we need we need
      pkg_cmd << "apt-get install -q -y " + packageList.join(" ") << " ; "
      host.vm.provision :shell, :inline => pkg_cmd

      scripts = [
      "clean.sh",
      ];
      scripts.each { |script| host.vm.provision :shell, :privileged => false, :path => "tools/vagrant/" << script }
    end
    scripts = [
      "compile.sh",
    ];
    scripts.each { |script| host.vm.provision :shell, :privileged => false, :path => "tools/vagrant/" << script }
  end
end
