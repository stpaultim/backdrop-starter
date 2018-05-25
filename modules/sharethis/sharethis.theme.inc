<?php
/**
 * @file
 * Theme functions for ShareThis module.
 */

/**
 * Generates markup for ShareThis widget.
 */
function theme_sharethis_widget($variables) {
  $property = $variables['property'];
  $product = $variables['product'];

  backdrop_add_js('//platform-api.sharethis.com/js/sharethis.js#property=' . $property . '&product=' . $product, array('type' => 'external'));
  return '<div class="sharethis-inline-share-buttons"></div>';
}
