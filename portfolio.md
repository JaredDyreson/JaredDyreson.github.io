---
title: Portfolio Projects
permalink: /portfolio/
---
<div class="row">

  {% for post in site.posts %}
    {% if post.categories contains 'portfolio' %}
    <div class="list-item">
    <p class="list-post-title">
        <img src="{% post.feature_img %}" />
        <a href="{{ site.baseurl }}{{ post.url }}">- {{ post.title }}</a> (<small>{{post.date | date: "%m/%d/%y" }}</small>)
        </p>
    </div>
    {% endif %}
  {% endfor %}
</div>

