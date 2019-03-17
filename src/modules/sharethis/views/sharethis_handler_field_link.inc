<?php
/**
 * @file
 * Field handler to display ShareThis links.
 */

/**
 * Field handler for ShareThis.
 */
class sharethis_handler_field_link extends views_handler_field_entity {

  function render($values) {
    if ($entity = $this->get_value($values)) {
      return $this->render_sharethis_link($entity);
    }
  }

  function render_sharethis_link($entity) {
    // Get all necessary settings.
    $data_options = sharethis_get_all_settings();

    return theme('sharethis_widget', array(
      'options' => $data_options,
      'services' => $data_options['services'],
      'title' => $entity->title,
      'url' => url('node/' . $entity->nid, array('absolute' => TRUE)),
    ));
  }
}
