---
title: Portfolio Projects
permalink: /portfolio/
---
<div class="row">

  {% for post in site.posts %}
    {% if post.categories contains 'portfolio' %}
     	 <div class="row">
           <div class="4u 12u$(mobile)">
             <div class="item">
                <a href="#" class="image fit"><img src="{{ 'assets/images/pic02.jpg' | relative_url }}" alt="Ipsum Feugiat" /></a>
                <header>
                  <h3>Ipsum Feugiat</h3>
                </header>
             </div>
	  </div>
    {% endif %}
  {% endfor %}
</div>

