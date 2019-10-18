<?php
/**
 * @file
 * Contains core functions for the Views module support.
 */

/*
 * Implements hook_views_plugins().
 *
 * This function defines the style plugin for flexslider views.
 */
function flexslider_views_views_plugins() {
  return array(
    'style' => array(
      'flexslider' => array(
        'title' => t('FlexSlider'),
        'help' => t('Display view results in a FlexSlider.'),
        'handler' => 'flexslider_views_plugin_style_flexslider',
        'theme' => 'flexslider_views',
        'theme file' => 'flexslider_views.theme.inc',
        'theme path' => backdrop_get_path('module', 'flexslider_views')  . '/templates',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
    ),
  );
}
