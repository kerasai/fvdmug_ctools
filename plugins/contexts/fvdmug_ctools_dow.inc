<?php

/**
 * @file
 * FVDMUG Day of Week context plugin.
 */

$plugin = array(
  'title' => t('Day'),
  'description' => t('A day of the week.'),
  'context' => 'fvdmug_ctools_context_dow_create',
  'edit form' => 'fvdmug_ctools_context_dow_settings_form',
  'defaults' => array('dow' => NULL, 'type' => NULL),
  'keyword' => 'day',
  'context name' => 'day',
  'convert list' => 'fvdmug_ctools_context_dow_convert_list',
  'convert' => 'fvdmug_ctools_context_dow_convert',
);

/**
 * Provide a form to configure the context.
 */
function fvdmug_ctools_context_dow_settings_form($form, &$form_state) {
  $conf = &$form_state['conf'];

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#id' => 'dow-type-select',
    '#options' => array(
      'current' => t('Current Day'),
      'select' => t('Select a Day'),
    ),
  );
  if ($conf['type'] !== NULL) {
    $form['type']['#default_value'] = $conf['type'];
  }

  $form['dow'] = array(
    '#type' => 'select',
    '#title' => t('Select a day'),
    '#options' => fvdmug_ctools_dow_options(),
    '#dependency' => array('dow-type-select' => array('select')),
    '#dependency_type' => 'visible',
  );
  if ($conf['dow'] !== NULL) {
    $form['dow']['#default_value'] = $conf['dow'];
  }

  return $form;
}

/**
 * Create the context.
 */
function fvdmug_ctools_context_dow_create($empty, $data = NULL, $conf = FALSE) {

  $context = new ctools_context('fvdmug_ctools_dow');
  $context->plugin = 'fvdmug_ctools_dow';

  if ($empty) {
    return $context;
  }

  // If configuration is supplied by the form use that data. Otherwise we assume
  // it's been supplied via relationship, context, etc.
  if ($conf) {
    switch ($data['type']) {
      case 'current':
        $data = date('w');
        break;
      case 'select':
        $data = $data['dow'];
    }
  }

  if ($data !== NULL) {
    $context->data = $data;
    return $context;
  }

}

/**
 * Declare "tokens" available for the context.
 */
function fvdmug_ctools_context_dow_convert_list() {
  return array(
    'name' => t('Name'),
    'abbrev' => t('Abbreviation'),
    'num' => t('Numeric'),
  );
}

/**
 * Provide values for tokens.
 */
function fvdmug_ctools_context_dow_convert($context, $type) {

  $days = fvdmug_ctools_dow_options();

  switch ($type) {
    case 'name':
      return $days[$context->data];
      break;
    case 'abbrev':
      return date('D', strtotime($days[$context->data]));
      break;
    case 'num':
      return $context->data;
      break;
  }

}
