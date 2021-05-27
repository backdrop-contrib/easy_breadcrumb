<?php if ($segments_quantity > 0): ?>
  <nav itemscope class="breadcrumb easy-breadcrumb" itemtype="<?php print $list_type; ?>" role="navigation">
    <h2 class="element-invisible">You are here</h2>
    <?php foreach ($breadcrumb as $i => $item): ?>
      <?php if ($is_link[$i]): ?>
        <span itemprop="itemListElement" itemscope itemtype="https://schema.org/ListItem">
          <?php print $item; ?>
          <meta itemprop="position" content="<?php print $i; ?>" />
        </span>
      <?php else: ?>
        <span itemprop="itemListElement">
          <?php print $item; ?>
        </span>
      <?php endif; ?>
      <?php if (($i + 1) != $segments_quantity || $separator_ending): ?>
        <span class="separator"><?php print $separator; ?></span>
      <?php endif; ?>
    <?php endforeach; ?>
  </nav>
<?php endif; ?>
