<?php
/**
 * @file
 * Dashboard block displaying BackdropCMS.org news items.
 */
class DashboardTriploNewsBlock extends Block {
  /**
   * {@inheritdoc}
   */
  public function __construct($plugin_name, array $data) {
    parent::__construct($plugin_name, $data);
  }
  /**
   * {@inheritdoc}
   */
  public function getTitle() {
    return !empty($this->settings['title']) ? check_plain($this->settings['title']) : t('Triplo Resources & News');
  }
  /**
   * {@inheritdoc}
   */
  public function getAdminTitle() {
    return t('Triplo News');
  }
  /**
   * {@inheritdoc}
   */
  public function getAdminPreview() {
    return t('Displays a news feed from Triplo.co.');
  }
  /**
   * {@inheritdoc}
   */
  public function getContent() {
    $feed = backdrop_http_request('http://sites.triplo.co/data/notifications');
    $links = array();
    if ($feed->code === '200') {
      $news = json_decode($feed->data);
      foreach ($news->notifications as $key => $notification) {
        $links[] = l(
            $notification->notification->title,
            $notification->notification->notification_link
          ) . ' - ' . $notification->notification->message;
      }
    }
    $build = array(
      '#theme' => 'dashboard_panel__news',
    );
    $build['welcome'] = array(
      '#type' => 'help',
      '#markup' => t(
        'Resources
        <ul>
            <li><a target="_blank" href="mailto:support@triplo.co">Email us</a></li>
            <li><a target="_blank" href="http://sites.triplo.co/faq">Triplo: Frequently Asked Questions</a></li>
        </ul>'
      ),
    );
    $build['notes'] = array(
      '#type' => 'help',
      '#markup' => t('Recent announcements from Triplo.'),
    );
    if (empty($links)) {
      $build['list'] = array(
        '#type' => 'markup',
        '#markup' => t('No news at this time.'),
      );
    }
    else {
      $build['list'] = array(
        '#theme' => 'item_list',
        '#items' => $links,
      );
    }
    $build['link'] = array(
      '#theme' => 'link',
      '#path' => 'http://sites.triplo.co/notifications',
      '#text' => t('More announcements'),
    );
    return $build;
  }
  /**
   * {@inheritdoc}
   */
  public function form(&$form, &$form_state) {
    parent::form($form, $form_state);
    $form['url'] = array(
      '#type' => 'help',
      '#markup' => t(
        'This block provides a news feed from Triplo.co. Its contents can not be edited.'
      ),
    );
  }
  /**
   * {@inheritdoc}
   */
  public function formSubmit($form, &$form_state) {
    parent::formSubmit($form, $form_state);
  }
}