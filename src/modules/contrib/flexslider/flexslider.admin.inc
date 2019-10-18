<?php
/**
 * @file
 * Administrative page callbacks for the flexslider module.
 */

/**
 * Form builder: Form for advanced settings.
 */
function flexslider_form_settings() {
  $form = array();

  $form['library'] = array(
    '#type' => 'fieldset',
    '#title' => 'Library',
  );

  // Debug mode toggle.
  $form['library']['debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug mode'),
    '#description' => t('Load the human-readable version of the FlexSlider library.'),
    '#default_value' => config_get('flexslider.settings', 'debug'),
    '#access' => user_access('administer flexslider'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the advanced module settings.
 */
function flexslider_form_settings_submit($form, &$form_state) {
  // Save to config.
  if (isset($form_state['values']['debug'])) {
    config_set('flexslider.settings', 'debug', $form_state['values']['debug']);
  }
  // Set a friendly message.
  backdrop_set_message(t('The configuration options have been saved.'));
}

/**
 * Callback function for flexSlider optionset list.
 */
function flexslider_optionset_list() {
  $header = array(
    array('data' => t('Title')),
    array('data' => t('Machine Name')),
    array('data' => t('Storage State')),
    array('data' => t('Operations')),
  );

  $storage_states = array(
    FLEXSLIDER_STORAGE_DEFAULT => t('Default (module-provided)'),
    FLEXSLIDER_STORAGE_OVERRIDDEN => t('Overridden'),
    FLEXSLIDER_STORAGE_CUSTOM => t('Custom'),
  );

  $optionsets = flexslider_optionset_load_all();
  $rows = array();
  foreach ($optionsets as $optionset) {
    $row = array();
    $row[] = array(
      'data' => check_plain($optionset['title']),
    );
    $row[] = array(
      'data' => check_plain($optionset['name']),
    );
    $row[] = array(
      'data' => $storage_states[$optionset['storage']],
    );
    $row[] = array(
      'data' => array(
        '#type' => 'operations',
        '#links' => _flexslider_get_operations($optionset),
      ),
    );

    $rows[] = array(
      'data' => $row,
    );
  }

  $table = array(
    'header' => $header,
    'rows' => $rows,
    'empty' => t('No flexslider optionsets found.'),
  );

  return theme('table', $table);
}

/**
 * Defines the form elements used to edit the FlexSlider library options
 *
 * @param array $options [optional]
 *  Pass in a set of default values for the options
 *
 * @return array
 *  Returns the option set array
 */
function flexslider_option_elements($options = array()) {
  $form = array();

  // General Slideshow and Animiation Settings
  $form['animation_slideshow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slideshow and Animation'),
  );

  $form['animation_slideshow']['animation'] = array(
    '#type' => 'select',
    '#title' => t('Animation Type'),
    '#options' => array(
      'fade'   => t('Fade'),
      'slide'  => t('Slide'),
    ),
    '#default_value' => isset($options['animation']) ? $options['animation'] : _flexslider_optionset_defaults('animation'),
  );

  $form['animation_slideshow']['direction'] = array(
    '#type' => 'select',
    '#title' => t('Slide Direction'),
    '#options' => array(
      'horizontal'   => t('Horizontal'),
      'vertical'  => t('Vertical'),
    ),
    '#default_value' =>  isset($options['direction']) ? $options['direction'] : _flexslider_optionset_defaults('direction'),
    '#states' => array(
      'visible' => array(
        ':input[name="animation"]' => array('value' => 'slide'),
      ),
    ),
  );

  $form['animation_slideshow']['animationSpeed'] = array(
    '#type' => 'number',
    '#title' => t('Animation Speed'),
    '#field_suffix' => t('milliseconds'),
    '#element_validate' => array('_flexslider_validate_positive_integer'),
    '#default_value' => isset($options['animationSpeed']) ? $options['animationSpeed'] : _flexslider_optionset_defaults('animationSpeed'),
  );

  $form['animation_slideshow']['slideshow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animate the slides automatically (slideshow).'),
    '#default_value' => isset($options['slideshow']) ? $options['slideshow'] : _flexslider_optionset_defaults('slideshow'),
  );

  // Build in support for easing plugin
  $easing_options = array('swing' => t('Swing'), 'linear' => t('Linear'));
  if (module_exists('jqeasing')) {
    $easing_options = array_merge($easing_options, _flexslider_jqeasing_options());
  }

  $form['animation_slideshow']['easing'] = array(
    '#type' => 'select',
    '#title' => t('Easing'),
    '#multiple' => FALSE,
    '#description' => t('Easing functions specify the speed at which an animation progresses at different points within the animation. <em>Linear</em> progresses at a constant pace throughout the animation, and <em>Swing</em> progresses slightly slower at the beginning and end of the animation than it does in the middle.'),
    '#options' => $easing_options,
    '#default_value' => isset($options['easing']) ? $options['easing'] : _flexslider_optionset_defaults('easing'),
  );

  $form['animation_slideshow']['smoothHeight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animate the height of the slider smoothly for slides of varying height (smoothHeight).'),
    '#default_value' => isset($options['smoothHeight']) ? $options['smoothHeight'] : _flexslider_optionset_defaults('smoothHeight'),
  );

  $form['animation_slideshow']['reverse'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reverse the animation direction (reverse).'),
    '#default_value' => isset($options['reverse']) ? $options['reverse'] : _flexslider_optionset_defaults('reverse'),
  );

  $form['animation_slideshow']['slideshowSpeed'] = array(
    '#type' => 'number',
    '#title' => t('Slideshow cycle speed (slideshowSpeed)'),
    '#field_suffix' => t('milliseconds'),
    '#element_validate' => array('_flexslider_validate_positive_integer'),
    '#default_value' => isset($options['slideshowSpeed']) ? $options['slideshowSpeed'] : _flexslider_optionset_defaults('slideshowSpeed'),
  );

  $form['animation_slideshow']['animationLoop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop the slideshow once it reaches the last slide.'),
    '#default_value' => isset($options['animationLoop']) ? $options['animationLoop'] : _flexslider_optionset_defaults('animationLoop'),
  );

  $form['animation_slideshow']['randomize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Randomize slide order (randomize).'),
    '#default_value' => isset($options['randomize']) ? $options['randomize'] : _flexslider_optionset_defaults('randomize'),
  );
  $form['animation_slideshow']['startAt'] = array(
    '#type' => 'number',
    '#title' => t('Starting Slide'),
    '#description' => t('For the first slide enter "0", for the second enter "1", etc. If you enter a value which is greater than the number of slides, the slider will default to the first slide.'),
    '#element_validate' => array('_flexslider_validate_positive_integer'),
    '#default_value' => isset($options['startAt']) ? $options['startAt'] : _flexslider_optionset_defaults('startAt'),
    '#states' => array(
      'visible' => array(
        ':input[name="randomize"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['animation_slideshow']['itemWidth'] = array(
    '#type' => 'number',
    '#title' => t('Carousel item CSS width'),
    '#field_suffix' => t('pixels'),
    '#description' => t('Box-model width of individual carousel items, including horizontal borders and padding. (This value must also be set with CSS. Setting informs FlexSlider of the width.)'),
    '#default_value' => isset($options['itemWidth']) ? $options['itemWidth'] : _flexslider_optionset_defaults('itemWidth'),
  );
  $form['animation_slideshow']['itemMargin'] = array(
    '#type' => 'number',
    '#title' => t('Carousel item CSS margin'),
    '#field_suffix' => t('pixels'),
    '#description' => t('Margin between carousel items. (This value must also be set with CSS. Setting informs FlexSlider of the CSS margin.)'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['itemMargin']) ? $options['itemMargin'] : _flexslider_optionset_defaults('itemMargin'),
  );
  $form['animation_slideshow']['minItems'] = array(
    '#type' => 'number',
    '#title' => t('Minimum number of carousel items that should be visible.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['minItems']) ? $options['minItems'] : _flexslider_optionset_defaults('minItems'),
  );
  $form['animation_slideshow']['maxItems'] = array(
    '#type' => 'number',
    '#title' => t('Maximum number of carousel items that should be visible.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['maxItems']) ? $options['maxItems'] : _flexslider_optionset_defaults('maxItems'),
  );
  $form['animation_slideshow']['move'] = array(
    '#type' => 'number',
    '#title' => t('Number of carousel items that should move on animation.'),
    '#description' => t('If set to 0, slider will move all visible items.'),
    '#default_value' => isset($options['move']) ? $options['move'] : _flexslider_optionset_defaults('move'),
  );

  // Navigation and Controls
  $form['nav_controls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation and Controls'),
  );
  $form['nav_controls']['directionNav'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show controls for previous/next navigation'),
    '#default_value' => isset($options['directionNav']) ? $options['directionNav'] : _flexslider_optionset_defaults('directionNav'),
  );
  $form['nav_controls']['prevText'] = array(
    '#type' => 'textfield',
    '#title' => t('Previous link text'),
    '#default_value' => isset($options['prevText']) ? $options['prevText'] : _flexslider_optionset_defaults('prevText'),
    '#states' => array(
      'visible' => array(
        ':input[name="directionNav"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['nav_controls']['nextText'] = array(
    '#type' => 'textfield',
    '#title' => t('Next link text'),
    '#default_value' => isset($options['nextText']) ? $options['nextText'] : _flexslider_optionset_defaults('nextText'),
    '#states' => array(
      'visible' => array(
        ':input[name="directionNav"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['nav_controls']['pausePlay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Pause/Play indicator'),
    '#default_value' => isset($options['pausePlay']) ? $options['pausePlay'] : _flexslider_optionset_defaults('pausePlay'),
  );
  $form['nav_controls']['pauseText'] = array(
    '#type' => 'textfield',
    '#title' => t('Pause indicator text'),
    '#default_value' => isset($options['pauseText']) ? $options['pauseText'] : _flexslider_optionset_defaults('pauseText'),
    '#states' => array(
      'visible' => array(
        ':input[name="pausePlay"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['nav_controls']['playText'] = array(
    '#type' => 'textfield',
    '#title' => t('Play indicator text'),
    '#default_value' => isset($options['playText']) ? $options['playText'] : _flexslider_optionset_defaults('playText'),
    '#states' => array(
      'visible' => array(
        ':input[name="pausePlay"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['nav_controls']['pauseOnAction'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause the slideshow when interacting with control elements (pauseOnAction).'),
    '#default_value' => isset($options['pauseOnAction']) ? $options['pauseOnAction'] : _flexslider_optionset_defaults('pauseOnAction'),
  );
  $form['nav_controls']['pauseOnHover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause the slideshow when hovering over slider, then resume when no longer hovering (pauseOnHover).'),
    '#default_value' => isset($options['pauseOnHover']) ? $options['pauseOnHover'] : _flexslider_optionset_defaults('pauseOnHover'),
  );
  $form['nav_controls']['controlNav'] = array(
    '#type' => 'select',
    '#title' => t('Paging controls to jump to individual slides.'),
    '#description' => t('Set to "Numeric pager" if using <em>Manual controls</em> (under Advanced Options).'),
    '#default_value' => isset($options['controlNav']) ? $options['controlNav'] : _flexslider_optionset_defaults('controlNav'),
    '#options' => array(
      0 => t('Off'),
      1 => t('Numeric pager'),
      'thumbnails' => t('Thumbnail pager'),
    )
  );
  $form['nav_controls']['thumbCaptions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add captions to thumbnails and remove them from the main slides (thumbCaptions).'),
    '#description' => t('<em>Requires FlexSlider Library 2.2+</em>.'),
    '#default_value' => isset($options['thumbCaptions']) ? $options['thumbCaptions'] : _flexslider_optionset_defaults('thumbCaptions'),
    '#states' => array(
      'visible' => array(
        ':input[name="controlNav"]' => array('value' => 'thumbnails'),
      ),
    ),
    '#element_validate' => array('_flexslider_validate_minimum_version_22'),
  );
  $form['nav_controls']['thumbCaptionsBoth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display both thumbnail captions and normal captions (thumbCaptionsBoth).'),
    '#description' => t('<em>Requires FlexSlider Library 2.2+</em>.'),
    '#default_value' => isset($options['thumbCaptionsBoth']) ? $options['thumbCaptionsBoth'] : _flexslider_optionset_defaults('thumbCaptionsBoth'),
    '#states' => array(
      'visible' => array(
        ':input[name="controlNav"]' => array('value' => 'thumbnails'),
      ),
    ),
    '#element_validate' => array('_flexslider_validate_minimum_version_22'),
  );
  $form['nav_controls']['keyboard'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow keyboard navigation with left/right arrow keys (keyboard).'),
    '#default_value' => isset($options['keyboard']) ? $options['keyboard'] : _flexslider_optionset_defaults('keyboard'),
  );
  $form['nav_controls']['multipleKeyboard'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow keyboard navigation to affect multiple sliders (multipleKeyboard).'),
    '#default_value' => isset($options['multipleKeyboard']) ? $options['multipleKeyboard'] : _flexslider_optionset_defaults('multipleKeyboard'),
  );
  $form['nav_controls']['mousewheel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow mousewheel navigation (mousewheel).'),
    '#default_value' => isset($options['mousewheel']) ? $options['mousewheel'] : _flexslider_optionset_defaults('mousewheel'),
    // @todo add check for jquery mousewheel library
  );
  $form['nav_controls']['touch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow touch swipe navigation (touch).'),
    '#default_value' => isset($options['touch']) ? $options['touch'] : _flexslider_optionset_defaults('touch'),
  );

  // Advanced Options
  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Options'),
  );
  $form['advanced']['namespace'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace'),
    '#description' => t('Prefix for the classes of all elements generated by FlexSlider.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['namespace']) ? $options['namespace'] : _flexslider_optionset_defaults('namespace'),
  );
  $form['advanced']['selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Selector'),
    '#description' => t('Must match a simple pattern, for example: <code>{container} > {slide}</code>.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['selector']) ? $options['selector'] : _flexslider_optionset_defaults('selector'),
  );
  $form['advanced']['sync'] = array(
    '#type' => 'textfield',
    '#title' => t('Sync'),
    '#description' => t('Mirror the actions performed on this slider with another slider.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['sync']) ? $options['sync'] : _flexslider_optionset_defaults('sync'),
  );
  $form['advanced']['asNavFor'] = array(
    '#type' => 'textfield',
    '#title' => t('Use as navigation'),
    '#description' => t('Turn this slider into thumbnail navigation for another slider.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => isset($options['asNavFor']) ? $options['asNavFor'] : _flexslider_optionset_defaults('asNavFor'),
  );

  $form['advanced']['initDelay'] =  array(
    '#type' => 'number',
    '#title' => t('Initialize Delay'),
    '#description' => t('Set an initialization delay, in milliseconds.'),
    '#default_value' => isset($options['initDelay']) ? $options['initDelay'] : _flexslider_optionset_defaults('initDelay'),
    //'#element_validate' => add validate on zero or greater integer
  );
  $form['advanced']['useCSS'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use CSS3 transitions.'),
    '#default_value' => isset($options['useCSS']) ? $options['useCSS'] : _flexslider_optionset_defaults('useCSS'),
  );
  $form['advanced']['video'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video support'),
    '#description' => t('Prevents the use of CSS3 3D Transforms, which may help avoid some graphical glitches.'),
    '#default_value' => isset($options['video']) ? $options['video'] : _flexslider_optionset_defaults('video'),
  );
  $form['advanced']['controlsContainer'] = array(
    '#type' => 'textfield',
    '#title' => t('Controls container'),
    '#description' => t('Declare which container the navigation elements should be appended to. Default container is the flexSlider element. Example use would be <code>.flexslider-container</code>, <code>#container</code>, etc.'),
    '#default_value' => isset($options['controlsContainer']) ? $options['controlsContainer'] : _flexslider_optionset_defaults('controlsContainer'),
  );
  $form['advanced']['manualControls'] = array(
    '#type' => 'textfield',
    '#title' => t('Manual controls'),
    '#description' => t('Declare custom control navigation. Example would be <code>.flex-control-nav li</code> or <code>#tabs-nav li img</code>, etc. The number of elements in your controlNav should match the number of slides/tabs. Note: <em>Paging controls</em> must be set to "Numeric pager" (under Navigation and controls).'),
    '#default_value' => isset($options['manualControls']) ? $options['manualControls'] : _flexslider_optionset_defaults('manualControls'),
  );

  return $form;
}

/**
 * Form builder: Form to add or edit an option set.
 */
function flexslider_form_optionset_edit($form, &$form_state, $optionset = array()) {
  // If the form has failed validation, don't loose the changes.
  if (!empty($form_state['optionset'])) {
    $optionset = $form_state['optionset'];
  }
  if (empty($optionset)) {
    $optionset = flexslider_optionset_create();
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#maxlength' => '255',
    '#title' => t('Title'),
    '#description' => t('A human-readable title for this option set.'),
    '#required' => TRUE,
    '#default_value' => $optionset['title'],
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#maxlength' => '255',
    '#machine_name' => array(
      'source' => array('title'),
      'exists' => 'flexslider_optionset_exists',
    ),
    '#required' => TRUE,
    '#default_value' => $optionset['name'],
  );
  $form['module'] = array(
    '#type' => 'value',
    '#default_value' => isset($optionset['module']) ? $optionset['module'] : NULL,
  );

  // Options Vertical Tab Group table
  $form['options'] = array(
    '#type' => 'vertical_tabs',
  );

  $default_options = flexslider_option_elements($optionset['options']);

  // Add the options to the vertical tabs section
  foreach ($default_options as $value) {
    $form['options'][] = $value;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for optionset add/edit form.
 */
function flexslider_form_optionset_edit_submit($form, &$form_state) {
  // Redirect to list page.
  $form_state['redirect'] = 'admin/config/media/flexslider';

  $values = $form_state['values'];

  // Build a base optionset.
  $optionset = array(
    'name' => $values['name'],
    'title' => $values['title'],
    'options' => array(),
  );
  if ($values['module'] != NULL) {
    $optionset['module'] = $values['module'];
  }

  // Remove base items from options.
  unset($values['name']);
  unset($values['title']);
  // Remove form elements from config.
  unset($values['submit']);
  unset($values['form_build_id']);
  unset($values['form_token']);
  unset($values['form_id']);
  unset($values['op']);
  // Remove storage state, must be computed.
  unset($values['storage']);

  // All other options should be saved in 'options' key.
  foreach ($values as $key => $value) {
    $optionset['options'][$key] = $value;
  }

  // Save to config.
  flexslider_optionset_save($optionset);

  // Set a friendly message.
  backdrop_set_message(t('@title configuration has been saved.', array('@title' => $optionset['title'])));
}

/**
 * Validate a form element that should have an integer value.
 */
function _flexslider_validate_positive_integer($element, &$form_state) {
  $value = $element['#value'];
  if ($value !== '' && (!is_numeric($value) || intval($value) != $value || $value < 0)) {
    form_error($element, t('%name must be a positive integer.', array('%name' => $element['#title'])));
  }
}

/**
 * Form builder; Form to delete a given option set.
 */
function flexslider_optionset_form_delete($form, &$form_state, $optionset) {
  $form_state['optionset'] = &$optionset;

  // Deleting an export in code will revert it.
  $op = (isset($optionset['overridden']) && $optionset['overridden']) ? 'Revert' : 'Delete';

  $question = t('Are you sure you want to @action the optionset @title?', array('@action' => backdrop_strtolower($op), '@title' => $optionset['title']));
  $path = 'admin/config/media/flexslider';
  $description = NULL;

  return confirm_form($form, $question, $path, $description, t($op), t('Cancel'));
}

/**
 * Submit handler for deleting (or reverting) an optionset.
 */
function flexslider_optionset_form_delete_submit($form, &$form_state) {
  $optionset = &$form_state['optionset'];

  if (isset($optionset['overridden']) && $optionset['overridden']) {
    $op = 'reverted';
    flexslider_optionset_revert($optionset);
  }
  else {
    $op = 'deleted';
    flexslider_optionset_delete($optionset);
  }

  backdrop_set_message(t('Optionset @title has been ' . $op . '.', array('@title' => $optionset['title'])));
  $form_state['redirect'] = 'admin/config/media/flexslider';
}

/**
 * Validate a form element that should have a number as value.
 */
function _flexslider_validate_minimum_version_22($element, &$form_state) {
  /* @todo
  $lib = libraries_detect('flexslider');
  if (!isset($lib['version'])) {
    backdrop_set_message(t('Unable to detect FlexSlider library version. Some options may not function properly. Please review the README.md file for installation instructions.'), 'warning');
  }
  else {
    $version = $lib['version'];
    $required = "2.2";

    if ($element['#value'] && !version_compare($version, $required, '>=')) {
      form_error($element, t('To use %name you must install FlexSlider version !required or higher.', array(
        '%name' => $element['#title'],
        '!required' => l($required, 'https://github.com/woothemes/FlexSlider/tree/version/2.2'),
      )));
    }
  }
  */
}

/**
 * Given a view, return a list of operations that can be performed on it.
 */
function _flexslider_get_operations($optionset) {
  $links = array();

  $links['edit'] = array(
    'title' => t('Edit'),
    'href' => 'admin/config/media/flexslider/edit/' . $optionset['name'],
  );
  /* @todo - restore clone ability
  $links['clone'] = array(
    'title' => t('Clone'),
    'href' => 'admin/config/media/flexslider/clone/' . $optionset['name'],
  );
  */
  if ($optionset['storage'] == FLEXSLIDER_STORAGE_CUSTOM) {
    $links['delete'] = array(
      'title' => t('Delete'),
      'href' => 'admin/config/media/flexslider/delete/' . $optionset['name'],
    );
  }
  elseif ($optionset['storage'] == FLEXSLIDER_STORAGE_OVERRIDDEN) {
    $links['revert'] = array(
      'title' => t('Revert'),
      'href' => 'admin/config/media/flexslider/revert/' . $optionset['name'],
    );
  }

  return $links;
}
