<?php
/**
 * @file
 * Template for outputting the default block styling within a Layout.
 *
 * Variables available:
 * - $classes: Array of classes that should be displayed on the block's wrapper.
 * - $title: The title of the block.
 * - $title_prefix/$title_suffix: A prefix and suffix for the title tag. This
 *   is important to print out as administrative links to edit this block are
 *   printed in these variables.
 * - $content: The actual content of the block.
 */
?>
<div class="row">
  <div class="offset-md-4 col-md-8 col-sm-12">
    <div class="primary-navigation <?php print implode(' ', $classes); ?>"<?php print backdrop_attributes($attributes); ?>>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h2 class="block-title"><?php print $title; ?></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <div class="block-content">
        <nav class="navbar navbar-expand-md navbar-light">
          <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#collapsibleNavbar">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="collapsibleNavbar">
            <?php print render($content); ?>
          </div>
        </nav>
      </div>
    </div>
  </div>
</div>