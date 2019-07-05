# Tribasis Theme
This theme is fork of the Basis theme from Backdrop Core as of July 1, 2019. 
The goal for this theme is simply to make improvements that make Basis more
flexible and easy to use out of the box.

## Responsive Strategy
Media queries and other responsive code should be mobile first. This means all
media queries should be `min-width`. Breakpoints are set in `em` as it works
better with accessibility technologies than px units do.

The breakpoints are:
* `(min-width: 25em)` - About `400px`
* `(min-width: 34em)` - About `544px`
* `(min-width: 48em)` - About `768px`
* `(min-width: 62em)` - About `992px`
* `(min-width: 75em)` - About `1200px`

## Classes that can be added to blocks in UI 

* hero-large           (default - height: 600px)
* hero-medium          (default - height: 400px)
* hero-small           (default - height: 200px)
* hero-extra-small     (default - height: 100px)

## CSS documentation
See [README.md in css directory](css/README.md).
