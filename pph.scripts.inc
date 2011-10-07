<?php


/**
 * Implementation of hook_voipscript_get_script_names()
 */
function pph_voipscript_get_script_names() {
  $script_names[] = 'pph_welcome_script';
  $script_names[] = 'pph_main_menu_script';
  $script_names[] = 'pph_play_story_script';
  $script_names[] = 'pph_record_story_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function pph_voipscript_load_script($script_name, $options=NULL) {

  require_once(dirname(__FILE__) . DIRECTORY_SEPARATOR . 'pph.prompts.inc');

  $script = NULL;
  switch($script_name) {
    default:
      break;

    case 'pph_welcome_script':
      $options['language'] = 'en';

      $script = new VoipScript('pph_welcome_script');
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
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_main_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('english_version');
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('spanish_version');
      $options['language'] = 'es';
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addHangup();
      break;

    case 'pph_main_menu_script':
      $script = new VoipScript('pph_main_menu_script');
      $language = $options['language'];

      $script->addLabel('introduction');
      $script->addGetInput(v('p_introduction', $language), 1);

      $script->addLabel('options_menu');
      $p_options_menu = v('p_options_menu', $language);
      $input_options = array(
        '1' => 'introduction',
        '2' => 'definition',
        '3' => 'minimum_wages',
        '4' => 'overtime_wages',
        '5' => 'days_of_rest',
        '6' => 'taxes',
        '7' => 'wage_deduction',
        '8' => 'insurance',
        '9' => 'record_story',
        '*' => 'redirect_call',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('definition');
      $options['story_id'] = 'definition';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('minimum_wages');
      $options['story_id'] = 'minimum_wages';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('overtime_wages');
      $options['story_id'] = 'overtime_wages';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('days_of_rest');
      $options['story_id'] = 'days_of_rest';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('taxes');
      $options['story_id'] = 'taxes';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('wage_deduction');
      $options['story_id'] = 'wage_deduction';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('insurance');
      $options['story_id'] = 'insurance';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('record_story');
      $script->addGosub('pph_record_message_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('redirect_call');
$script->addSay('This is where the call is going to be redirected to DWU. ');
      $script->addGoto('go_back');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

      $script->addLabel('go_back');
      $script->addSay(v('p_thank_you', $language));
      $script->addReturn();
      break;

    case 'pph_play_story_script':
      $script = new VoipScript('pph_play_story_script');
      $story_id = $options['story_id'];
$script->addSay("About to play story id: $story_id. ");
      switch($story_id) {
        default:
$script->addSay("Invalid story id: $story_id. ");
$script->addLog("Invalid story id: $story_id. ");
return;
          break;
        case 'definition':
          $prompt = v('p_definition', $language);
          break;
        case 'minimum_wages':
          $prompt = v('p_minimum_wages', $language);
          break;
        case 'overtime_wages':
          $prompt = v('p_overtime_wages', $language);
          break;
        case 'days_of_rest':
          $prompt = v('p_days_of_rest', $language);
          break;
        case 'taxes':
          $prompt = v('p_taxes', $language);
          break;
        case 'wage_deduction':
          $prompt = v('p_wage_deduction', $language);
          break;
        case 'insurance':
          $prompt = v('p_insurance', $language);
          break;
      }
      $script->addSay($prompt);
      $script->addReturn();
      break;

    case 'pph_record_story_script':
      $script = new VoipScript('pph_record_story_script');
$script->addSay('This is where the personal story is going to be recorded.');
      $script->addReturn();
      break;

  }

  return $script;
}


/**
 * Internal functions
 */

function _pph_get_latest_announcement($language) {

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

