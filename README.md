# ENPH253
<b>INSTALLATION</b>

1. Visual Studio with the Arduino extension must be installed first. 
2. In the default Arduino folder (../Documents/Arduino), install the TINAH library (http://projectlab.engphys.ubc.ca/wp-content/uploads/TINAH_DocumentsFolder.zip)
and replace some of the files in Arduino/libraries/TINAH with those in this repository (Modified TINAH Library).

<b> MENU SYSTEM </b>

Menu navigation is based on the two pushbuttons (start and stop) and two analog knobs on the TINAH. A short stopbutton press (~200ms) switches menus, short startbutton enables editing menu parameters, long startbutton (>1 second) saves menu parameters to EEPROM, and long stopbutton loads parameters from the EEPROM. 

Menu order is defined under switchMenu() in menu.cpp.
