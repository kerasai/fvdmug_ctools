<?php

/**
 * @file
 */

$plugin = array(
  'title' => t('FVDMUG Stuff'),
);

/**
 * Declare the content types we'll provide.
 */
function fvdmug_ctools_fvdmug_ctools_content_type_content_types() {

  $types['dow'] = array(
    'title' => t('Day of week, abbrev'),
    'category' => t('FVDMUG'),
    'edit form' => 'fvdmug_ctools_dow_content_type_settings_form',
    'required context' => array(
      new ctools_context_required(t('Day'), 'fvdmug_ctools_dow'),
    ),
  );

  $types['dow_full'] = array(
    'title' => t('Day of week, full.'),
    'category' => t('FVDMUG'),
    'edit form' => 'fvdmug_ctools_dow_content_type_settings_form',
    'required context' => array(
      new ctools_context_required(t('Day'), 'fvdmug_ctools_dow'),
    ),
  );

  return $types;
}

/**
 * Settings form, needed to provide context selection and title override.
 */
function fvdmug_ctools_dow_content_type_settings_form($form, &$form_state) {
  return $form;
}

/**
 * Provide a pane title for the admin screen.
 */
function fvdmug_ctools_fvdmug_ctools_content_type_admin_title($subtype, $conf, $context) {
  $day = $context[0];

  switch ($subtype) {
    case 'dow':
    case 'dow_full':
      return t('Day of week: %day', array('%day' => $day->identifier));
      break;
  }
}

/**
 * Provide a pane description for the admin screen.
 */
function fvdmug_ctools_fvdmug_ctools_content_type_admin_info($subtype, $conf, $context) {
  $info = new stdClass();

  switch ($subtype) {
    case 'dow':
      $info->title = t('Abbreviation.');
      $info->content = t('An abbreviation for the day of the week.');
      break;
    case 'dow_full':
      $info->title = t('Full.');
      $info->content = t('The full name for the day of the week.');
      break;
  }

  return $info;
}

/**
 * Render the content.
 */
function fvdmug_ctools_fvdmug_ctools_content_type_render($subtype, $conf, $arg, $context) {
  $day = $context[0];
  $days = fvdmug_ctools_dow_options();

  $content = new stdClass();

  switch ($subtype) {
    case 'dow':
      $content->title = t('Abbreviation');
      $content->content = date('D', strtotime($days[$day->data]));
      break;
    case 'dow_full':
      $content->title = t('Full');
      $content->content = $days[$day->data];
      break;
  }

  return $content;
}
