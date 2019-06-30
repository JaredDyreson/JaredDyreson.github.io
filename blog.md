---
title: Blog
permalink: /blog/
---

<h2>Resources</h2>
<h2>Linux System Administration</h2>
<div class="content list">
  {% for post in site.posts %}
    {% if post.categories contains 'blog' %}
    <h2>Workflow</h2>
    {% elsif post.categories contains 'workflow' %}
    <div class="list-item">
    <p class="list-post-title">
        <a href="{{ site.baseurl }}{{ post.url }}">- {{ post.title }}</a> (<small>{{post.date | date: "%m/%d/%y" }}</small>)
	<p>{{ post.categories }}</p>
        </p>
    </div>
    {% endif %}
  {% endfor %}
</div>

