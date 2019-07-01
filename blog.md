---
title: Blog
permalink: /blog/
---

{% for category in site.categories %}
  <li>{{ category | first }}
    <ul>
    {% for post in category.last %}
      {% if post == 'portfolio' %}
        {% continue %}
      {% else %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
      {% endif %}
    {% endfor %}
    </ul>
  </li>
{% endfor %}
