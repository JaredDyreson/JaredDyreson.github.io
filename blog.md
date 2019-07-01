---
title: Blog
permalink: /blog/
---

{% for category in site.categories %}
  <li><a name="{{ category | first }}">{{ category | first }}</a>
    <ul>
    {% for post in category.last %}
      {% if category.last == 'portfolio' %}
        {% continue %}
      {% else %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
      {% endif %}
    {% endfor %}
    </ul>
  </li>
{% endfor %}
