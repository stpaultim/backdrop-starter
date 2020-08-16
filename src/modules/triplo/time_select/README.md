Config Batch Upload
===================

DESCRIPTION
-----------
A proof of concept for the ability to upload a batch of config files that
would add a feature to Backdrop CMS.

At this early stage, this module adds a "recipe" tab to the configuration 
menu options. Users can upload a batch of configuration files through the
UI. The configuration files must be in tarball with .tar format.

Sample "recipes" or "config features" available in .tar format:
https://github.com/backdrop-contrib/config_recipes

Here is how I planned to start:

1) User uploads a batch of config files in a tarball
2) Tarball is stored in temp directory
3) Staging directory is cleared
4) Batch of config in tarball is decompressed and dropped into staging directory
5) All other currently config in "active" directory is copied into Staging
6) User then uses "Syncronize" feature to add their config recipe/feature

LICENSE
---------------    

This project is GPL v2 software. See the LICENSE.txt file in this directory 
for complete text.

CURRENT MAINTAINERS
---------------    

- Tim Erickson (https://github.com/stpaultim/)

CREDITS   
--------------- 

Development supported by Triplo LLC - http://www.triplo.co
