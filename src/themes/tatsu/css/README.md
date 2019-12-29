Tatsu has incorporated the base css files from Basis and added it's own
overriding CSS.

We have tried to adhere to the premise of Basis, which inludes very granular 
CSS files so that a sub theme can override only the files it needs to and 
inherit the rest.

## CSS Files
Directories:
* Basis - files taken directly from the Backdrop Core theme Basis.
  This directory should not be altered expect to inherit updates
  to the Core Basis theme.
* Tatsu - CSS files specifically added by Tatsu
* Bootstrap - We've included Bootstrap 

The types of CSS files in the theme include:
* Base      - Normalizes rendering across browsers.
* Layout    - Modifies page layout.
* Component - Specific styles for individual pieces of functionality.
* Skin      - The colors, fonts, and aesthetic CSS

A good way to think about overriding files:
 * Start by overriding skin.css with the colors and fonts you'd prefer
 * If there are other changes to be made, copy over the files one by one and
   override as needed

 ### To override a CSS file:
 Declare it in your .info file with the same file name.
 The file in Basis with the same name will not be loaded. The file in the active
 theme will be used in it's place.

 # CSS Guidelines
 [See Backdrop's CSS Standards](https://api.backdropcms.org/css-standards)
