---
title: Blog
permalink: /blog/
---
<ul>
{% for category in site.categories %}
  <h2>{{ category | first }}</h2>
    <ul>
      {% for post in category.last %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
      {% endfor %}
    </ul>
{% endfor %}
</ul>
