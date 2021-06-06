### How to release ? 

1. `chmod 755 release.sh`

2. modify `Mini-PhotoShop.desktop`

   ```shell
   #!/usr/bin/env xdg-open                                                         
   
   [Desktop Entry]
   Version=1.0
   Type=Application
   Terminal=false
   Exec=/your/path/to/Mini-PhotoShop/release/Mini-PhotoShop.sh           
   Name=Mini-PhotoShop
   Comment=version 1.0 
   Icon=/your/path/to/Mini-PhotoShop/images/logo.png

3. `sudo ./release.sh`



### How to clean ?

`sudo ./clean.sh`

