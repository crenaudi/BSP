void renderPlayerView (t_player *player)
	{
		[..]

		renderBSPNode (numnodes-1);//les SEGS visibles sont projetés à l'écran via une table de recherche et découpés via un tableau d'occlusion. Les murs sont dessinés sous forme de colonne de pixels. La taille d'une colonne est déterminée par la distance du POV du joueur, la position Y d'une colonne via la hauteur par rapport à la lecture. La base et le haut des murs génèrent des plans visuels, une structure utilisée pour rendre le sol et le plafond (appelés appartements).
		drawPlanes ();//buf colonne de pixel rendu a l'ecran
		drawMasked ();//enemi, obj et etc

	}
