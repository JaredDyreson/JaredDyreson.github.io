---
title: Blog
permalink: /blog/
---

{% for category in site.categories %}
  <h2>{{ category | first }}</h2>
    <ul>
    {% for post in category.last %}
      {% if post == 'portfolio' %}
        {% continue %}
      {% else %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
      {% endif %}
    {% endfor %}
    </ul>
{% endfor %}
