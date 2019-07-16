<?php
/**
 * @file
 * Admin functions for ShareThis module.
 */

/**
 * This is the main settings form for the admin page.
 */
function sharethis_settings_form($form, &$form_state) {
  $config = config('sharethis.settings');
  $form = array('#config' => 'sharethis.settings');

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );

  $property = $config->get('property');
  $product = $config->get('product');

  if (!isset($property) || $property == '') {
    $help = array(
      '<strong>Step 1:</strong> Visit <a href="https://www.sharethis.com">https://www.sharethis.com</a>',
      '<strong>Step 2:</strong> Select your services, buttons, and other preferences.',
      '<strong>Step 3:</strong> Copy Property ID perameter from the script tag generated for your use, and enter it below.',
    );
    $form['settings']['steps']= array(
      '#type' => 'markup',
      '#markup' => theme('item_list', array('title' => t('Set-up instructions'), 'items' => $help)),
    );
    $example = '19d7f735a397b70018a015fd';
  }
  else {
    $example = $property;
  }

  $form['settings']['property'] = array(
    '#title' => t("Property"),
    '#description' => t('How to get the Property: sharethis.js#property=<strong>' . $example . '</strong>&product=' . $product),
    '#type' => 'textfield',
    '#default_value' => $property,
    '#required' => TRUE,
  );

  $form['settings']['product'] = array(
    '#title' => t("Product"),
    '#description' => t('How to get the Product: sharethis.js#property=' . $example . '&product=<strong>' . $product . '</strong>'),
    '#type' => 'textfield',
    '#default_value' => $product,
    '#required' => TRUE,
  );

  // Set which content types will have ShareThis added.
  $content_types = array();
  $entity_info = entity_get_info('node');
  foreach ($entity_info['bundles'] as $bundle => $bundle_info) {
    $content_types[$bundle] = t($bundle_info['label']);
  }

  $displayed_on = $config->get('node_types');
  $form['settings']['node_types'] = array(
    '#title' => t('Display ShareThis on the following content types:'),
    '#description' => t('The ShareThis links can be ordered on the <a href="@url">Manage Displays</a> section for each content type.', array('@url' => url('admin/structure/types'))),
    '#type' => 'checkboxes',
    '#options' => $content_types,
    '#default_value' => !empty($displayed_on)? $displayed_on: array(),
  );

  $form['settings']['comments'] = array(
    '#title' => t('Display ShareThis on comments'),
    '#type' => 'checkbox',
    '#default_value' => $config->get('comments'),
    '#access' => module_exists('comment'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return system_settings_form($form);
}
