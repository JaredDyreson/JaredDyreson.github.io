---
title: Portfolio Projects
permalink: /portfolio/
---
<div class="row">

  {% for post in site.posts %}
    {% if post.categories contains 'portfolio' %}
    <a href="{{ post.url | prepend: site.baseurl }}">
      <div class="col-xs-12 col-sm-6 col-md-4">
        <div class="panel panel-primary">
          <div class="panel-heading">
              {{ post.title }}
          </div>
          <div class="panel-body">
            {{ post.excerpt }}
          </div>
        </div>
      </div>
    </a>
    {% endif %}
  {% endfor %}
</div>

