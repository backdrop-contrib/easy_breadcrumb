<?php
/**
 * @file
 * Module's settings form, and form handlers.
 */

/**
 * General configuration form.
 *
 * @return Assoc
 *   renderable form.
 */
function easy_breadcrumb_settings_form() {
  backdrop_add_js(backdrop_get_path('module', 'easy_breadcrumb') . '/js/easy_breadcrumb.admin.js');

  $config = config('easy_breadcrumb.settings');
  $form = array('#config' => 'easy_breadcrumb.settings');

  // Fieldset for grouping general settings fields.
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['general']['separator'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Breadcrumb separator:'),
    '#default_value' => $config->get('separator'),
  );
  $form['general']['separator_end'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumb separator after the final breadcrumb.'),
    '#default_value' => $config->get('separator_end'),
  );

  // Fieldset for grouping text settings.
  $form['general']['first'] = array(
    '#type' => 'fieldset',
    '#title' => t('First Breadcrumb'),
    '#collapsible' => FALSE,
  );
  $form['general']['first']['include_home'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include a link to the home page as the first breadcrumb.'),
    '#default_value' => $config->get('include_home'),
  );
  $form['general']['first']['home_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Home page link text:'),
    '#default_value' => $config->get('home_title'),
    '#attributes' => array('placeholder' => 'Home'),
    '#states' => array(
      'visible' => array(
        ':input[name="include_home"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['general']['final'] = array(
    '#type' => 'fieldset',
    '#title' => t('Final Breadcrumb'),
    '#collapsible' => FALSE,
  );
  $form['general']['final']['include_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the current page as the final breadcrumb.'),
    '#default_value' => $config->get('include_title'),
  );
  $form['general']['final']['title_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make the current page breadcrumb into a link (not recommended).'),
    '#default_value' => $config->get('title_link'),
    '#states' => array(
      'visible' => array(
        ':input[name="include_title"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['general']['paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general']['paths']['include_invalid_paths'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include invalid paths as plain-text breadcrumbs.'),
    '#default_value' => $config->get('include_invalid_paths'),
  );
  // Formats the excluded paths array as line separated list of paths
  // before displaying them.
  $excluded_paths_arr = $config->get('excluded_paths');
  $excluded_paths = @join("\r\n", $excluded_paths_arr);
  $form['general']['paths']['excluded_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Breadcrumb paths to be excluded:'),
    '#description' => t('Enter paths or simple regular expressions. Place one on each line. Example: <em>report</em> or <em>report/2[0-9][0-9][0-9].</em>'),
    '#default_value' => $excluded_paths,
  );
  $form['general']['disable_default_breadcrumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the system breadcrumbs.'),
    '#default_value' => $config->get('disable_default_breadcrumb'),
    '#description' => t('When unchecked, breadrcumbs may appear twice on the page.'),
  );

  $form['general']['disable_admin_breadcrumb'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the system breadcrumbs in the admin theme.'),
    '#default_value' => $config->get('disable_admin_breadcrumb'),
    '#description' => t('When the admin theme is the default theme, this setting will have no effect.'),
  );
  $site_theme = config_get('system.core', 'theme_default');
  $admin_theme = config_get('system.core', 'admin_theme');
  if ($site_theme == $admin_theme) {
    $form['general']['disable_admin_breadcrumb']['#disabled'] = TRUE;
  }

  // Fieldset for grouping text settings.
  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumb text'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['text']['html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow HTML tags in breadcrumb text.'),
    '#default_value' => $config->get('html'),
  );

  $form['text']['title_from_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the page title (when available) instead of the text from the URL.'),
    '#default_value' => $config->get('title_from_page'),
  );

  $form['text']['segment_url_text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the text from the URL instead of the page title.'),
    '#description' => t("This setting is usefull for views page displays with contextual filters."),
    '#default_value' => $config->get('segment_url_text'),
  );

  $form['text']['truncate_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit the breadcrumb text to a maximum number of characters.'),
    '#default_value' => $config->get('truncate_mode'),
  );

  $form['text']['Limit the breadcrumb'] = array(
    '#type' => 'number',
    '#title' => t('Breadcrumb character Limit'),
    '#description' => t('Breaks at word boundaries. Example: When set to 10, <em>Long page title</em> will be <em>Long page...</em>'),
    '#default_value' => $config->get('truncate_length'),
    '#attributes' => array('placeholder' => '25'),
    '#states' => array(
      'visible' => array(
        ':input[name="truncate_mode"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="truncate_mode"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['text']['truncate_dots'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add an elipsis (...) to shortened titles.'),
    '#default_value' => $config->get('truncate_dots'),
    '#states' => array(
      'visible' => array(
        ':input[name="truncate_mode"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="truncate_mode"]' => array('checked' => FALSE),
      ),
    ),
  );

  $replaced_titles = $config->get('replaced_titles');
  $form['text']['replaced_titles'] = array(
    '#type' => 'textarea',
    '#title' => t('Breadcrumb text to be replaced'),
    '#description' => t('Enter current breadcrumb and replacement text seperated by two colons (::). Place one breadcrumb on each line.'),
    '#attributes' => array('placeholder' => 'Administration::Admin'),
    '#default_value' => $replaced_titles,
  );

  // Fieldset for grouping capitalization settings.
  $form['caps'] = array(
    '#type' => 'fieldset',
    '#title' => t('Capitalization'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['caps']['caps_mode'] = array(
    '#type' => 'select',
    '#title' => t('Breadcrumb capitalization'),
    '#options' => array(
      'none' => t('None'),
      'ucfirst' => t('Only capitalize the first letter (ucfirst)'),
      'ucwords' => t('Capitalize the first letter of each word (ucwords)'),
      'ucall' => t('Capitalize all the letters (strtoupper)'),
      'ucforce' => t('Only capitalize all the letters in the words defined below'),
    ),
    '#description' => t("Example: 'blog/once-upon-a-time' -> 'Home » Blog » Once upon a time'."),
    '#default_value' => $config->get('caps_mode'),
  );

  // Formats the ignored-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_ignored_words_arr = $config->get('caps_ignored_words');
  $capitalizator_ignored_words = @join(' ', $capitalizator_ignored_words_arr);

  $form['caps']['caps_ignored_words'] = array(
    '#type' => 'textfield',
    '#size' => '180',
    '#title' => t('Words that should not be capitalized'),
    '#description' => t('Separate each word with a space. Note: The first word of each breadcrumb will always be capitalized.'),
    '#default_value' => $capitalizator_ignored_words,
    '#states' => array(
      'visible' => array(
        ':input[name="caps_mode"]' => array('value' => 'ucwords'),
      ),
      'invisible' => array(
        ':input[name="caps_mode"]' => array('!value' => 'ucwords'),
      )
    )
  );

  // Formats the forced-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_forced_words_arr = $config->get('caps_forced_words');
  $capitalizator_forced_words = @join(' ', $capitalizator_forced_words_arr);

  $form['caps']['caps_forced_words'] = array(
    '#type' => 'textfield',
    '#size' => '180',
    '#title' => t('Words that should have all letters capitalized'),
    '#description' => t('Separate each word with a space. Useful for capitalizing your organization or brand name.'),
    '#default_value' => $capitalizator_forced_words,
    '#attributes' => array('placeholder' => 'NASA'),
    '#states' => array(
      'visible' => array(
        ':input[name="caps_mode"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="caps_mode"]' => array('!value' => 'ucforce'),
      )
    )
  );

  $form['caps']['caps_forced_case'] = array(
    '#type' => 'checkbox',
    '#title' => t('Compare case when matching words'),
    '#default_value' => $config->get('caps_forced_case'),
    '#states' => array(
      'visible' => array(
        ':input[name="caps_mode"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="caps_mode"]' => array('!value' => 'ucforce'),
      )
    ),
    '#description' => t('When unchecked, backdrop will match both Backdrop and BACKDROP.'),
  );

  $form['caps']['caps_forced_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Capitalize the first letters of each breadcrumb.'),
    '#default_value' => $config->get('caps_forced_first'),
    '#states' => array(
      'visible' => array(
        ':input[name="caps_mode"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="caps_mode"]' => array('!value' => 'ucforce'),
      )
    )
  );

  return system_settings_form($form);
}

/**
 * Validate handler for easy_breadcrumb_settings_form().
 */
function easy_breadcrumb_settings_form_validate($form, &$form_state) {
  // Prepare the list of ignored words for storing them as an array.
  // Replaces line-endings by spaces and splits words by spaces.
  // E.g.: array('of','and').
  $ignored_words_arr = array();
  $ignored_words = $form_state['values']['caps_ignored_words'];
  $ignored_words = preg_replace('/\r*\n+/', ' ', $ignored_words);
  $ignored_words = trim($ignored_words);
  $ignored_words_arr_aux = $ignored_words === '' ? array() : preg_split('/\s+/', $ignored_words);
  foreach ($ignored_words_arr_aux as $word) {
    $ignored_words_arr[$word] = $word;
  }

  $excluded_paths_arr = array();
  $excluded_paths = $form_state['values']['excluded_paths'];
  $excluded_paths = trim($excluded_paths);
  $excluded_paths = preg_replace('/\s+/', "\r\n", $excluded_paths);
  $excluded_paths_arr_aux = $excluded_paths === '' ? array() : preg_split('/\r*\n+/', $excluded_paths);
  foreach ($excluded_paths_arr_aux as $path) {
    $path = trim($path, "/");
    $excluded_paths_arr[$path] = $path;
  }

  $forced_words_arr = array();
  $forced_words = $form_state['values']['caps_forced_words'];
  $forced_words = preg_replace('/\r*\n+/', ' ', $forced_words);
  $forced_words = trim($forced_words);
  $forced_words_arr_aux = $forced_words === '' ? array() : preg_split('/\s+/', $forced_words);
  foreach ($forced_words_arr_aux as $word) {
    $forced_words_arr[$word] = $word;
  }
  // Updates the $form_state before passing it to the Backdrop system.
  $form_state['values']['caps_ignored_words'] = $ignored_words_arr;
  $form_state['values']['excluded_paths'] = $excluded_paths_arr;
  $form_state['values']['caps_forced_words'] = $forced_words_arr;
}
