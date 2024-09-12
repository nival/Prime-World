@echo off

:: Export fb_users
svn export -r HEAD https://svn.nivalnetwork.com/testpw-ro/fb_users .\fb_users --force --no-auth-cache

python admin_users.py --add_fb_users_file=.\fb_users\fb_users.txt:1000 > admin_users_.log