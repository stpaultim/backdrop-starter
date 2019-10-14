<?php $tag = $block->subject?'section':'div';?>
<<?php print $tag;
?> id="block-<?php print $block->module.'-'.$block->delta?>" class="<?php print implode(' ', $classes);?> clearfix"<?php print backdrop_attributes($attributes);
?>>
  <div class="block-inner">
<?php print render($title_prefix);?>
    <?php if ($block->subject):?>
      dpm($block);
      <h2 class="block-title"<?php print $title_attributes;?>><?php print $block->subject?></h2>
<?php endif;?>
    <?php print render($title_suffix);?>
    <div class="content" <?php print backdrop_attributes($content_attributes);?>>
<?php print $content;?>
    </div>
  </div>
</<?php print $tag;?>> <!-- /block-inner /block -->