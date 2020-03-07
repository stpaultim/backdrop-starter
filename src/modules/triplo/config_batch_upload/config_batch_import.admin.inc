<?php


  /**
   * Form callback; Provide a form for importing a full set of configuration.
   */
  function config_batch_import_import_recipe_form(array $form, array &$form_state) {
    $form['description'] = array(
      '#markup' => '<p>' . t('Import a batch of config files.') . '</p>',
    );
    $form['import_tarball'] = array(
      '#type' => 'managed_file',
      '#title' => t('Select an archive containing a batch of config files.'),
      '#description' => t('This file should be a compressed archive with the extension "tar".'),
      '#upload_validators' => array(
        'file_validate_extensions' => array('tar gz'),
      ),
      '#progress_indicator' => 'bar',
      '#upload_location' => 'public://recipe',
    );

    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Stage config'),
    );
    return $form;
  }

  function config_batch_import_import_recipe_form_submit(array &$form, array &$form_state) {
    if ($fid = $form_state['values']['import_tarball']) {
      // Empty out the existing staging directory.
      $config_storage = config_get_config_storage('staging');
      $config_storage->deleteAll();

      // Convert the file URI to a file path that is readable by ArchiverTar.
      $file = file_load($fid);
      $config_storage->importArchive($file->uri);
      file_delete($file->fid);
      // Dump active directory

      // Move all images files
      $files = glob("../config/active/*.*");
      foreach($files as $file){
        $file_to_go = str_replace("../config/active/","../config/staging/",$file);
        copy($file, $file_to_go);
      }
      backdrop_set_message(t('Check to see if your configuration was imported properly. If so, import 
      this batch by using the "Import all" button.'));
      $form_state['redirect'] = 'admin/config/development/configuration';
    }
  }
