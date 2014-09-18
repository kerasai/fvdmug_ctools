<?php

$plugin = array(
  'title' => t("Day: Current DOW"),
  'description' => t('Determine if a day is the current day of the week.'),
  'callback' => 'fvdmug_ctools_dow_current',
  'default' => array(),
  'summary' => 'fvdmug_ctools_dow_current_summary',
  'required context' => array(
    new ctools_context_required(t('Day'), 'fvdmug_ctools_dow'),
  ),
);

/**
 * Compare the context to the current day of the week.
 */
function fvdmug_ctools_dow_current($conf, $context) {
  // Grab the conext we're analyzing.
  $day = $context[0];

  // Determine if it's the current day.
  return $day->data == date('w');
}

/**
 * Provide a textual summary of the config.
 */
function fvdmug_ctools_dow_current_summary($conf, $context) {
  $day = $context[0];
  return t('%day is current day.', array('%day' => $day->identifier));
}
