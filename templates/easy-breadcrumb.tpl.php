<?php if ($segments_quantity > 0): ?>
  <nav itemscope class="breadcrumb easy-breadcrumb" itemtype="<?php print $list_type; ?>" role="navigation">
    <h2 class="element-invisible">You are here</h2>
    <?php foreach ($breadcrumb as $i => $item): ?>
      <span itemprop="itemListElement" itemscope itemtype="http://schema.org/ListItem">
        <?php print $item; ?>
        <meta itemprop="position" content="<?php print $i; ?>" />
      </span>
      <?php if (($i + 1) != $segments_quantity || $separator_ending): ?>
         <span class="separator"><?php print $separator; ?></span>
      <?php endif; ?>
    <?php endforeach; ?>
  </nav>
<?php endif; ?>
