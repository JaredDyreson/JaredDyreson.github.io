---
title: Blog
permalink: /blog/
---
<ul>
{% for category in site.categories %}
  <li><b name="{{ category | first }}">{{ category | first }}</b>
    <ul>
      {% for post in category.last %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
      {% endfor %}
    </ul>
{% endfor %}
</ul>
