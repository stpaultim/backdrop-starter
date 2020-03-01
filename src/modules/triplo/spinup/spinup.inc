<?php

/**
 * @file
 * This is the Form API Tutorial, originally from the Backdrop handbook.
 *
 * It goes through 10 form examples of increasing complexity to demonstrate
 * Backdrop Form API.
 *
 * Links are provided inline for the related handbook pages.
 *
 * @see http://DOCUMENTATION_PENDING/node/262422
 */

function form_example_tutorial() {
  return t('This is a set of 10 form tutorials tied to the <a href="http://DOCUMENTATION_PENDING/node/262422">Backdrop handbook</a>. The same Backdrop code works essentially unmodified in Backdrop.');
}


function spinup_form($form, &$form_state) {

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A simple form'),
  );
  // This is the first form element. It's a textfield with a label, "Name"
  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
  );
  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

function spinup_form_submit($form, &$form_state) {
//  $dir = backdrop_get_path('module', 'spinup');

  $command = "modules/triplo/spinup/testing.sh";
  backdrop_set_message($command);
  $result = exec($command, $response, $return_code);
  backdrop_set_message(
    print_r(array('result was'=>$result, 'response was'=>$response, 'return code'=>$return_code ),1)
  );
  watchdog('spinup', 'spinup ran 2');
}
