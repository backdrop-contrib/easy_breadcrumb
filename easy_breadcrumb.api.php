<?php
/**
 * @file
 * API documentation.
 */

/**
 * Allows modules to alter the path to calculate the breadcrumb.
 *
 * @param string $path
 *   The current path returned by backdrop_get_path_alias().
 */
function hook_easy_breadcrumb_path_alter(&$path) {
  // Replace the path to calculate the breadcrumb for
  // the printmail page in the print module.
  $args = arg();
  if ($args[0] == 'printmail') {
    $args[] = array_shift($args);
    $path = implode('/', $args);
  }
}

/**
 * Allows modules to alter the breadcrumb displayed in the block.
 *
 * @param array $breadcrumb
 *   The breadcrumb array returned to render in the block.
 */
function hook_easy_breadcrumb_breadcrumb_alter(&$breadcrumb) {
  // Remove the last breadcrumb element for node pages.
  $args = arg();
  if ($args[0] == 'node') {
    array_pop($breadcrumb);
  }
}

/**
 * Allows other modules to remove breadcrumbs when this module is verifying
 * if the given path should be excluded from the breadcrumb list.
 *
 * This allows testing at each level of the breadcrumb build process (i.e.
 * check /node, check /node/1234, check /node/1234/webform, etc.)
 *
 * @param bool $excluded | Delete if TRUE
 * @param string $url | URL of the breadcrumb link
 */
function hook_easy_breadcrumb_exclude_path_alter(&$excluded, $url) {
  if ($url == 'node/12345') {
    $excluded = TRUE;
  }
}
