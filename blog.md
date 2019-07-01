---
title: Blog
permalink: /blog/
---
<ul>
{% for category in site.categories %}
	{% if category contains "portfolio" %}
		{% break %}
	{% else %}
		<b name="{{ category | first }}">{{ category | first }}</b>
		<ul>
			{% for post in category.last %}
				<li><a href="{{ post.url }}">{{ post.title }}</a><(<small>{{post.date | date: "%m/%d/%y" }}</small>)/li>
			{% endfor %}
		</ul>
	{% endif %}
{% endfor %}
</ul>
