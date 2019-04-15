<?php
/**
 * @file
 * template.php
 */

/**
 * Prepares variables for layout templates.
 *
 * @see layout.tpl.php
 */
function tripoly_preprocess_layout(&$variables) {
  if ($variables['is_front']) {
    // Add a special front-page class.
    $variables['classes'][] = 'layout-front';
    // Add a special front-page template suggestion.
    $original = $variables['theme_hook_original'];
    $variables['theme_hook_suggestions'][] = $original . '__front';
    $variables['theme_hook_suggestion'] = $original . '__front';
  }
}


/**
 * Implements hook_links().
 */
function tripoly_links__header_menu($menu){
  $menu['attributes']['class'] = array('menu','nav','navbar-nav');
  if($navbar_menu_position = theme_get_setting('tripoly_navbar_menu_position')){
    $menu['attributes']['class'][] = $navbar_menu_position;
  }
  return theme_links($menu);
}


function tripoly_menu_tree__main_menu($variables) {
  return '<ul class="navbar-nav mr-auto">' . $variables['tree'] . '</ul>';
}

function tripoly_menu_link(array $variables) {
	$a_dropdown = '';
	$a_class_dropdown = 'nav-link';
	if ($variables['element']['#below']) {
		$a_dropdown = 'dropdown';
		$a_class_dropdown = 'nav-link dropdown-toggle';

	}
	// print_r($variables['element']);
	//add class for a
	$variables['element']['#below']['attributes']['class'][] = 'aaaaaaaaaaaaaaaaaa';
	$variables['element']['#localized_options']['attributes']['class'][] = $a_class_dropdown;
	$variables['element']['#localized_options']['attributes']['data-toggle'][] = $a_dropdown;

	$element = $variables['element'];
	$sub_menu = '';
	$dropdown = '';
	$linktext = '' . $element['#title'] . '';

	if ($element['#below']) {
		$sub_menu = '<div class="dropdown-menu" aria-labelledby="navbarDropdown">' . backdrop_render($element['#below']) . '</div>';
		$dropdown = 'dropdown';
	}

	$element['#localized_options']['html'] = TRUE;

	$output = l($linktext, $element['#href'], $element['#localized_options'], $variables);
	return '<li class="nav-item '.$dropdown.'">' . $output . $sub_menu . '</li>';  
}

