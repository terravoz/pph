<?php


/**
 * Implementation of hook_voipscript_get_script_names()
 */
function pcn_voipscript_get_script_names() {
  $script_names[] = 'pcn_welcome_script';
  $script_names[] = 'pcn_options_script';
  $script_names[] = 'pcn_play_announcement_script';
  $script_names[] = 'pcn_record_message_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function pcn_voipscript_load_script($script_name, $options=NULL) {

  require_once(dirname(__FILE__) . DIRECTORY_SEPARATOR . 'pcn.prompts.inc');

  $script = NULL;
  switch($script_name) {
    default:
      break;

    case 'pcn_welcome_script':
      $options['language'] = 'en';

      $script = new VoipScript('pcn_welcome_script');
      $script->addSetVoice('woman');
      $script->addSet('max_session_duration', 0);

      // log the call
      $log_msg = t("Call from %caller_number on @date (id: %call_id)",
          array('@date' => format_date(time())));
      $script->addLog($log_msg, 'MDT');

      $script->addSay(v('p_greetings'));

      $script->addLabel('language_selection');
      $p_main_menu = v('p_language_selection_menu');
      $input_options = array(
        '1' => 'english_version',
        '2' => 'spanish_version',
        '3' => 'portuguese_version',
        '4' => 'creole_version',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_main_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('english_version');
      $script->addGosub('pcn_options_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('spanish_version');
      $options['language'] = 'es';
      $script->addGosub('pcn_options_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('portuguese_version');
      $options['language'] = 'pt';
      $script->addGosub('pcn_options_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('creole_version');
      $options['language'] = 'ht';
      $script->addGosub('pcn_options_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addHangup();
      break;

    case 'pcn_options_script':
      $script = new VoipScript('pcn_options_script');
      $language = $options['language'];

      $p_options_menu = v('p_options_menu', $language);
      $input_options = array(
        '1' => 'play_announcement',
        '*' => 'record_message',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('play_announcement');
      $script->addGosub('pcn_play_announcement_script', $options);
      $script->addGoto('go_back');

      $script->addLabel('record_message');
      $script->addGosub('pcn_record_message_script', $options);
      $script->addGoto('go_back');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

      $script->addLabel('go_back');
      $script->addSay(v('p_thank_you', $language));
      $script->addReturn();
      break;

    case 'pcn_play_announcement_script':
      $script = new VoipScript('pcn_play_announcement_script');
      $announcement = _pcn_get_latest_announcement($options['language']);
      $script->addSay($announcement);
      $script->addReturn();
      break;

    case 'pcn_record_message_script':
      $script = new VoipScript('pcn_record_message_script');
$script->addSay('This is where the message is going to be recorded.');
      $script->addReturn();
      break;

  }

  return $script;
}


/**
 * Internal functions
 */

function _pcn_get_latest_announcement($language) {

  $sql = "SELECT n.nid AS nid FROM {node} n WHERE (n.type = 'announcement') AND (n.status <> 0) AND (n.promote <> 0)";
  $result = db_query($sql);
  // the following code assumes that there will be only one announcement promoted at a time
  $o = db_fetch_object($result);
  if($o) {
    $n = node_load($o->nid);
    $field_audio_title_name = 'field_audio_title_' . $language;
    $field_audio_title = $n->$field_audio_title_name;
    if($field_audio_title[0]) {
      $audio_title_url = url($field_audio_title[0]['filepath'], array('absolute' => TRUE));
      $announcement = $audio_title_url;
    }
    $field_audio_body_name = 'field_audio_body_' . $language;
    $field_audio_body = $n->$field_audio_body_name;
    if($field_audio_body[0]) {
      $audio_body_url = url($field_audio_body[0]['filepath'], array('absolute' => TRUE));
      $announcement .= " $audio_body_url";
    }
  }
  else {
    $announcement = 'No announcements recorded in the system.';
  }

  return $announcement;
}

