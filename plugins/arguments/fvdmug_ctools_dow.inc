<?php

$plugin = array(
  'title' => t("DOW: Abbreviation"),
  'keyword' => 'node',
  'description' => t('Creates a day-of-the-week context from a day\'s abbreviation.'),
  'context' => 'fvdmug_ctools_argument_dow',
);

/**
 * Analyze an argument and attempt to generate a context from it.
 */
function fvdmug_ctools_argument_dow($arg = NULL, $conf = NULL, $empty = FALSE) {

  // Sometimes we won't have actual data to work with, for example admin screens.
  if ($empty) {
    return ctools_context_create_empty('fvdmug_ctools_dow');
  }

  // Determine if the argument is one of the abbreviations we'll accept.
  $abbrevs = array('sun', 'mon', 'tue', 'wed', 'thu', 'fri', 'sat');
  $dow = array_search($arg, $abbrevs);

  // If it's good, pass it off to the CTools context creation functionality.
  if ($dow !== FALSE) {
    return ctools_context_create('fvdmug_ctools_dow', $dow);
  }
}
