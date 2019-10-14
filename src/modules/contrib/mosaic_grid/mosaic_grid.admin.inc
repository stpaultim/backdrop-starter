<?php
/**
 * @file
 * Administration page callbacks for the Mosaic Grid module.
 */

/**
 * Form constructor for the Mosaic Grid settings form.
 */
function mosaic_grid_admin_form($form, &$form_state) {
  $config = config('mosaic_grid.settings');

  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['appearance']['loader_style'] = array(
    '#type' => 'select',
    '#title' => t('Loader Style'),
    '#options' => array(
      'none'               => t('None'),
      'spinning_ring'      => t('Spinning Ring'),
      'spinning_ring_thin' => t('Spinning Ring Thin'),
      'floating_balls'     => t('Floating Balls'),
      'three_dots'         => t('Three Dots'),
      'square_blocks'      => t('Square Blocks'),
      'vertical_blocks'    => t('Vertical Blocks'),
    ),
    '#default_value' => $config->get('loader_style'),
    '#description' => t('Sets style for animated loader icon that is displayed while image is being loaded.'),
  );
  
  $form['appearance']['loader_color'] = array(
    '#type' => 'color',
    '#title' => t('Loader Color'),
    '#description' => t("Sets loader color."),
    '#default_value' => $config->get('loader_color'),
    '#states' => array(
      'invisible' => array(
        ':input[name="loader_style"]' => array('value' => 'none'),
      ),
    ),
  );
  
  $form['appearance']['caption_style_override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Customize caption style'),
    '#description' => t("Enables changing caption size and colors. This will
      override style provided by the theme. Uncheck if you would like the theme
      to control caption style."),
    '#default_value' => $config->get('caption_style_override'),
  );
  
  $form['appearance']['caption_font_color'] = array(
    '#type' => 'color',
    '#title' => t('Caption Font Color'),
    '#description' => t("Sets caption font color."),
    '#default_value' => $config->get('caption_font_color'),
    '#states' => array(
      'visible' => array(
        ':input[name="caption_style_override"]' => array('checked' => TRUE),
      ),
    ),
  );
  
  $form['appearance']['caption_opacity'] = array(
    '#type' => 'number',
    '#title' => t('Caption Background Opacity'),
    '#description' => t("Sets caption background opacity."),
    '#default_value' => $config->get('caption_opacity'),
    '#min' => 0,
    '#max' => 100,
    '#field_suffix' => t('%'),
    '#states' => array(
      'visible' => array(
        ':input[name="caption_style_override"]' => array('checked' => TRUE),
      ),
    ),
  );
  
  $form['appearance']['caption_font_size'] = array(
    '#type' => 'number',
    '#title' => t('Caption Font Size'),
    '#description' => t("Sets size of caption text."),
    '#default_value' => $config->get('caption_font_size'),
    '#min' => 0,
    '#max' => 100,
    '#field_suffix' => t('pt'),
    '#states' => array(
      'visible' => array(
        ':input[name="caption_style_override"]' => array('checked' => TRUE),
      ),
    ),
  );
  
  $form['appearance']['caption_padding'] = array(
    '#type' => 'number',
    '#title' => t('Caption Padding'),
    '#description' => t("Sets amount of background around caption text."),
    '#default_value' => $config->get('caption_padding'),
    '#min' => 0,
    '#max' => 100,
    '#field_suffix' => t('pt'),
    '#states' => array(
      'visible' => array(
        ':input[name="caption_style_override"]' => array('checked' => TRUE),
      ),
    ),
  );
  
  $form['appearance']['show_empty_images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show empty images'),
    '#description' => t("Enable this to show empty space with warning for images
      that have their file missing. By default such images are ignored and 
      not displayed in the grid."),
    '#default_value' => $config->get('show_empty_images'),
  );

  $form['lazyload'] = array(
    '#type' => 'fieldset',
    '#title' => t('Lazy Loading'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['lazyload']['lazyload_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Lazy Loading'),
    '#description' => t("If enabled then images are loaded only when they get
      within a visible page area. This considerably optimises page loading time
      where it contains many images. If you use some other module to lazy 
      load images on your site then you may want to disable this option."),
    '#default_value' => $config->get('lazyload_enabled'),
  );
  
  $form['lazyload']['lazyload_edgeY'] = array(
    '#type' => 'number',
    '#title' => t('Offset'),
    '#description' => t("The offset controls how early you want the elements to be
      loaded before they are visible. For example, value 100 means 100px before an
      element is visible it will start loading. Zero value means only images that are
      inside visible area will be loaded."),
    '#default_value' => $config->get('lazyload_edgeY'),
    '#min' => 0,
    '#max' => 9999,
    '#field_suffix' => t('pix'),
    '#states' => array(
      'visible' => array(
        ':input[name="lazyload_enabled"]' => array('checked' => TRUE),
      ),
    ),
  );
  
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  return $form;
}

/**
 * Saves configuration settings when the form is submitted.
 */
function mosaic_grid_admin_form_submit($form, &$form_state) {
  $config = config('mosaic_grid.settings');
  
  $config->set('loader_style',           $form_state['values']['loader_style']);
  $config->set('loader_color',           $form_state['values']['loader_color']);
  $config->set('caption_style_override', $form_state['values']['caption_style_override']);
  $config->set('caption_font_color',     $form_state['values']['caption_font_color']);
  $config->set('caption_opacity',        $form_state['values']['caption_opacity']);
  $config->set('caption_padding',        $form_state['values']['caption_padding']);
  $config->set('caption_font_size',      $form_state['values']['caption_font_size']);
  $config->set('show_empty_images',      $form_state['values']['show_empty_images']);
  $config->set('lazyload_enabled',       $form_state['values']['lazyload_enabled']);
  $config->set('lazyload_edgeY',         $form_state['values']['lazyload_edgeY']);
  
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}