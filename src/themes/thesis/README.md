Thesis
======

Thesis extends Basis, the default theme in Backdrop. More precisely, it doesn't
do much on its own, but it provides a place which lets you extend Basis easily.
Thesis provides a good start to give your Backdrop site a different look.

Thesis as a sub-theme
---------------------

Thesis is a sub-theme of Basis. In turn, Basis serves as base theme for Thesis.
As a sub-theme, Thesis inherits most resources of Basis.
When you start to use Thesis, your Backdrop site will look exactly like Basis.
However, Thesis comes with an empty `skin-thesis.css` which makes it easy to
override the CSS styles of Basis and/or to add your custom styles.

Installation
------------

- Install and enable Thesis using the official Backdrop CMS instructions at
https://backdropcms.org/guide/themes.
- Go to *Administer > Site building > Themes*, and make Thesis the active, default theme.

Usage
-----

Open the file `css/skin-thesis.css`, and add your styles.

### Override a Basis style
Example: Override Basis' blue link color with a pink one.

```
a {
  color: #e91e63;
}
```

### Add your own custom style
Example: Provide the main layout wrapper with a light grey background.

```
.l-wrapper {
  background: #f5f5f5;
}
```

Advanced usage
--------------

Apart from CSS styles, Basis includes template files, theme color settings and more.
To override template, JavaScript or PHP files in Thesis, or to make use of
theme settings, refer to the following resources about sub-theming.

### Basis
- https://github.com/backdrop/backdrop/blob/1.x/core/themes/basis/README.md
- https://github.com/backdrop/backdrop/blob/1.x/core/themes/basis/css/README.md
- https://backdropcms.org/news/build-sub-theme-basis-default-frontend-theme-backdrop

### API
- https://api.backdropcms.org/documentation/creating-sub-themes

Alternatives to Thesis
----------------------

### Write your own Basis sub-theme

Writing your sub-theme from scratch can be fun, you will learn a lot, and it
gives you the most freedom. Please refer to the sub-theming resources above.

### Build a Basis sub-theme using Drush

If you like Drush, check the `backdrop-subtheme-basis` command: `drush sb`.
Tutorial: https://howtobackdrop.com/posts/drush-subtheme-basis-command

### Install the Tatsu theme

Tatsu is a sub-theme of Basis that allows a site editor or manager to make
maximum color and visual customizations through the user interface.
Project: https://backdropcms.org/project/tatsu

### Install the CSS Injector module
CSS Injector allows you to add CSS to Backdrop based on configurable rules.
It's useful for adding simple CSS tweaks without modifying the theme.
Project: https://backdropcms.org/project/css_injector

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/thesis/issues

Current Maintainers
-------------------

- [Olaf Grabienski](https://github.com/olafgrabienski)

Credits
-------

- Wes Ruvalcaba (https://github.com/wesruv) and others for the Basis theme.
- Laryn Kragt Bakker (https://github.com/laryn) for the idea to call this theme "Thesis".

License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for the complete text.
