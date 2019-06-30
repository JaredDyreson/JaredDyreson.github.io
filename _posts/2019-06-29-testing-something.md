---
title: Something
permalink: /something/
---

<div class="content list">
  {% for post in site.posts %}
    {% if post.categories contains something %}
    <div class="list-item">
      <p class="list-post-title">
        <a href="{{ site.baseurl }}{{ post.url }}">- {{ post.title }}</a>
      </p>
    </div>
    {% endif %}
  {% endfor %}
</div>

<hr>
{% endfor %}

