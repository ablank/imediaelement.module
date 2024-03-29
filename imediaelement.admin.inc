<?php
/**
 * @file
 * Admin only functionality for the imediaelement module.
 */

/**
 * Menu form callback; Display the MediaElement admin form.
 */
function imediaelement_admin_form() {
  $form = array();
  $bool = array(1, 0);
  $libraries = libraries_get_libraries();
  $libpath = libraries_get_path('imediaelement', FALSE);

  // Detect if the library is available. If it is not available display message.
  if (!isset($libraries['imediaelement'])) {
    $form['message'] = array(
      '#markup' => '<p>' . t('The "imediaelement" library is not installed. Please download the library from <a href="!url">MediaElementjs.com</a> and place it in your libraries folder.', array('!url' => 'http://mediaelementjs.com')) . '</p>',
    );
  }

  $form['imediaelement_skin'] = array(
    '#title' => t('Player Skin'),
    '#type' => 'select',
    '#options' => array(
      $libpath . '/dist/css/mediaelement_dark.min.css' => t('ME Dark'),
      $libpath . '/dist/css/mediaelement_light.min.css' => t('ME Light'),
      $libpath . '/dist/css/mediaelement_large_dark.min.css' => t('ME Large Dark'),
      $libpath . '/dist/css/mediaelement_large_light.min.css' => t('ME Large Light'),
      $libpath . '/dist/css/mediaelementplayer.min.css' => t('Original ME'),
    ),
    '#default_value' => variable_get('imediaelement_skin', $libpath . '/dist/css/mediaelement_dark.min.css'),
  );

  $form['imediaelement_sitewide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable MediaElement site wide'),
    '#default_value' => variable_get('imediaelement_sitewide', TRUE),
  );

  $form['imediaelement_ctrl_alwaysShowControls'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always Show Controls'),
    '#default_value' => variable_get('imediaelement_ctrl_alwaysShowControls', FALSE),
  );

  $form['imediaelement_ctrl_nativecontrols'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force native controls on android & iOS.'),
    '#default_value' => variable_get('imediaelement_ctrl_nativecontrols', FALSE),
  );

  $form['imediaelement_ctrl_playpause'] = array(
    '#type' => 'checkbox',
    '#title' => t('Play / Pause'),
    '#options' => $bool,
    '#default_value' => variable_get('imediaelement_ctrl_playpause', TRUE),
  );

  $form['imediaelement_ctrl_volume'] = array(
    '#type' => 'checkbox',
    '#title' => t('Volume'),
    '#options' => $bool,
    '#default_value' => variable_get('imediaelement_ctrl_volume', TRUE),
  );

  $form['imediaelement_ctrl_current'] = array(
    '#type' => 'checkbox',
    '#title' => t('Current Time'),
    '#options' => $bool,
    '#default_value' => variable_get('imediaelement_ctrl_current', TRUE),
  );

  $form['imediaelement_ctrl_duration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Total Time'),
    '#options' => $bool,
    '#default_value' => variable_get('imediaelement_ctrl_duration', TRUE),
  );

  $form['imediaelement_ctrl_progress'] = array(
    '#type' => 'checkbox',
    '#title' => t('Progress Bar'),
    '#options' => $bool,
    '#default_value' => variable_get('imediaelement_ctrl_progress', TRUE),
  );

  $form['imediaelement_ctrl_fullscreen'] = array(
    '#title' => t('Enable Fullscreen Video'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('imediaelement_ctrl_fullscreen', TRUE),
  );

  $form['imediaelement_ctrl_startVolume'] = array(
    '#title' => t('Start Volume'),
    '#type' => 'textfield',
    '#size' => 8,
    '#default_value' => variable_get('imediaelement_ctrl_startVolume', '0.75'),
  );

  // Display a sample video. We add the library here because we cannot be sure
  // it is otherwise included in the page.
  drupal_add_library('imediaelement', 'imediaelement');
  drupal_add_js(drupal_get_path('module', 'imediaelement') . '/imediaelement.min.js');
  drupal_add_js(array('imediaelementAll' => TRUE), array('type' => 'setting'));
  $form['test'] = array(
    '#markup' => '<table>'
    . '<thead><tr><th>Demo</th><tr></thead>'
    . '<tbody><tr><td style="text-align:center">'
    . '<video width="360" height="200" id="player1">'
    . '<source type="video/youtube" src="//youtu.be/6zpxRB2vT0Y">'
    . '<p>Your browser leaves much to be desired.</p></video>'
    . '</td></tr></tbody></table>',
  );

  return system_settings_form($form);
}
// enableAutosize	clickToPlayPause: hideVideoControlsOnLoad	pauseOtherPlayers.
