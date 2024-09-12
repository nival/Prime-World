#/bin/bash
cd ..
echo -e "clean *.pyc\n"
find . -name "*.pyc" -exec rm -rf {} \;
echo -e "svn up --force\n"
svn up --force
echo -e "chown -R dduka:dduka ./* \n"
chown -R dduka:dduka ./*
echo -e "chown -R pwcastle:pwcastle ./logs/* \n"
chown -R pwcastle:pwcastle ./logs ./logs/*
#chown -R pwcastle:pwcastle ./pwctl/etc/init.d/*
#chown -R www-data:www-data ./application/log/
