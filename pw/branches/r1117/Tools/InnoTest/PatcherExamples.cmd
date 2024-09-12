@echo off
python Patcher.py --action CreateProduct --product Test --auth http://pw-updates.SITE/nival.ffs
python Patcher.py --action CreateProject --product Test --project P0 
python Patcher.py --action CreateRelease --product Test --project P0 --release 0.13.3 --source Versions\pvp-pbt\123
python Patcher.py --action CreateRelease --product Test --project P0 --release 0.13.4 --source Versions\pvp-pbt\124
python Patcher.py --action DeployContent --product Test --project P0 --release 0.13.3 --ftp ftp://pw-updates.SITE --user pwcdn --password password
python Patcher.py --action DeployContent --product Test --project P0 --release 0.13.4 --ftp ftp://pw-updates.SITE --user pwcdn --password password
python Patcher.py --action DeployDDN --product Test --project P0 --release 0.13.3 --ddnemail vhost7@domain.com --ddnpassword password
python Patcher.py --action DeployDDN --product Test --project P0 --release 0.13.4 --ddnemail vhost7@domain.com --ddnpassword password
python Patcher.py --action DeployPackage --product Test --project P0 --release 0.13.3 --ftp ftp://pw-updates.SITE --user pwcdn --password password 
python Patcher.py --action DeployPackage --product Test --project P0 --release 0.13.4 --ftp ftp://pw-updates.SITE --user pwcdn --password password
python Patcher.py --action MakePatch --product Test --project P0 --release 0.13.5 --source Versions\pvp-pbt\125 --ftp ftp://pw-updates.SITE --user pwcdn --password password --ddnemail vhost7@domain.com --ddnpassword password

python Patcher.py --action CreateProject --product Test --project P1 
python Patcher.py --action MakePatch --product Test --project P1 --release 0.13.1 --source Versions\lobby-pbt\123 --ftp ftp://pw-updates.SITE --user pwcdn --password password --ddnemail vhost7@domain.com --ddnpassword password



