/** @file andnotpostlist.h
 * @brief Return items which are in A, unless they're in B
 */
/* Copyright 1999,2000,2001 BrightStation PLC
 * Copyright 2002 Ananova Ltd
 * Copyright 2003,2004,2009,2011 Olly Betts
 * Copyright 2009 Lemur Consulting Ltd
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef OM_HGUARD_ANDNOTPOSTLIST_H
#define OM_HGUARD_ANDNOTPOSTLIST_H

#include "branchpostlist.h"

/** A postlist generated by taking one postlist (the left-hand postlist),
 *  and removing any documents which are in the other (right-hand) postlist.
 *
 *  The weight for a posting is the weight in the left-hand postlist.
 */
class AndNotPostList : public BranchPostList {
    private:
	Xapian::docid lhead, rhead;

	/// Number of documents in the database this postlist is across
	Xapian::doccount dbsize;

	PostList *advance_to_next_match(double w_min, PostList *ret);
    public:
	Xapian::doccount get_termfreq_max() const;
	Xapian::doccount get_termfreq_min() const;
	Xapian::doccount get_termfreq_est() const;
	TermFreqs get_termfreq_est_using_stats(
	    const Xapian::Weight::Internal & stats) const;

	Xapian::docid  get_docid() const;
	double get_weight() const;
	double get_maxweight() const;

	double recalc_maxweight();

	PostList *next(double w_min);
	PostList *skip_to(Xapian::docid did, double w_min);
	bool   at_end() const;

	std::string get_description() const;

	/** Return the document length of the document the current term
	 *  comes from.
	 */
	virtual Xapian::termcount get_doclength() const;

	virtual Xapian::termcount get_unique_terms() const;

	AndNotPostList(PostList *left,
		       PostList *right,
		       MultiMatch *matcher_,
		       Xapian::doccount dbsize_);

	PostList *sync_and_skip_to(Xapian::docid id,
				   double w_min,
				   Xapian::docid lh,
				   Xapian::docid rh);

	/** get_wdf() for ANDNOT postlists returns the wdf of the left hand
	 * side.
	 */
	Xapian::termcount get_wdf() const;

	Xapian::termcount count_matching_subqs() const;
};

#endif /* OM_HGUARD_ANDNOTPOSTLIST_H */
