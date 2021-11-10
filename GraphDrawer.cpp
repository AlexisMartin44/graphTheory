//
//  GraphDrawer.cpp
//  PiscineING2
//
//  Created by Titouan Lermite on 26/04/2020.
//  Copyright � 2020 Titouan Lermite. All rights reserved.
//

#include "GraphDrawer.h"
#include <algorithm>
#include <limits>

GraphDrawer::GraphDrawer(std::string path, int width, int height) : m_outputPath(path), m_width(width), m_height(height)
{ }

void GraphDrawer::Draw(Graph g, bool draw_text, bool adapt_size)
{
    IndicesWrapper iw;
    Draw(g, iw, draw_text);
}

void GraphDrawer::Draw(Graph g, IndicesWrapper iw, bool draw_text, bool adapt_size)
{
    double maximumX = 0, maximumY = 0, minimumX = std::numeric_limits<int>::max(), minimumY = std::numeric_limits<int>::max();
    bool test = false;
    m_rayon =  Closest(g.GetSommets());
    Svgfile svg(m_outputPath, m_width, m_height);

    auto c = Colors(iw);
    auto ar = AdaptRadius(iw);

    for(auto s : g.GetSommets())
    {
        if(s.GetX() > maximumX)
            maximumX = s.GetX();
        if(s.GetX() < minimumX)
            minimumX = s.GetX();
        if(s.GetY() > maximumY)
            maximumY = s.GetY();
        if(s.GetY() < minimumY)
            minimumY = s.GetY();
    }

    double proportionalityX = ((m_width - 2*MARGE) * (1 / (maximumX-minimumX)));
    double proportionalityY = ((m_height - 2*MARGE) * (1 / (maximumY-minimumY)));
    double x1, y1, x2, y2, x3 = 0.0, y3 = 0.0, temp;

    double dec = (15 * m_height) / 6000;
    if(dec < 15)
        dec = 15;

    m_rayon = std::max(MIN_RADIUS, std::min(m_rayon * proportionalityX - 1, m_rayon * proportionalityY - 1));

    proportionalityX = ((m_width - 2*MARGE - 2*m_rayon) * (1 / (maximumX-minimumX)));
    proportionalityY = ((m_height - 2*MARGE - 2*m_rayon) * (1 / (maximumY-minimumY)));

    for(auto s : g.GetSommets())
    {
        svg.AddSommet(m_rayon + proportionalityX * (s.GetX() - minimumX) + MARGE, m_rayon + proportionalityY * (s.GetY() - minimumY) + MARGE,
                      adapt_size ? m_rayon * ar[s.GetId()] : m_rayon, c.size() != 0 ? c[s.GetId()] : "rgb(255, 0, 0)", s.GetName(), s.GetId(), iw.Size() != 0 ? iw.GetIndices()[s.GetId()] : -1, draw_text);
    }

    for(auto a : g.GetAretes())
    {
        test = false;
        if(g.GetDeleted().count(a.GetId())==0)
        {
            x1 = proportionalityX * (g.GetSommets()[a.GetOrigin()].GetX() - minimumX) + MARGE;
            y1 = proportionalityY * (g.GetSommets()[a.GetOrigin()].GetY() - minimumY) + MARGE;
            x2 = proportionalityX * (g.GetSommets()[a.GetTarget()].GetX() - minimumX) + MARGE;
            y2 = proportionalityY * (g.GetSommets()[a.GetTarget()].GetY() - minimumY) + MARGE;
            if(g.GetOriente())
            {
                for(auto b : g.GetSiblings(a.GetTarget()))
                {
                    if(b.second.GetId() == a.GetOrigin())
                    {
                        x3 = (x2 - x1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                        y3 = (y2 - y1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                        test = true;

                        temp = x3;
                        x3 = y3;
                        y3 = -temp;
                    }
                }
            }
            if(!test)
                svg.AddArete(m_rayon + x1, m_rayon + y1, m_rayon + x2, m_rayon + y2,  adapt_size ? m_rayon * ar[a.GetOrigin()] : m_rayon, adapt_size ? m_rayon * ar[a.GetTarget()] : -1, "rgb(0, 0, 0)", 1, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId(), draw_text);
            else
                svg.AddArete(m_rayon + x1 + x3*dec, m_rayon + y1 + y3*dec, m_rayon + x2 + x3*dec, m_rayon + y2 + y3*dec,  adapt_size ? m_rayon * ar[a.GetOrigin()] * cos( atan(dec / m_rayon) ) : m_rayon * cos( atan(dec / m_rayon) ),
                             adapt_size ? m_rayon * ar[a.GetTarget()] * cos( atan(dec / m_rayon) ) : -1,
                               "rgb(0, 0, 0)", 1, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId());
        }
    }
}

std::vector<std::string> GraphDrawer::Colors(IndicesWrapper iw)
{
    if(iw.Size() == 0)
        return {};
    std::vector<std::string> c(iw.Size(), "rgb(");
    std::vector<double> mean_deviation(iw.Size());

    double mean = 0;
    for(auto i : iw.GetIndices())
    {
        mean += i;
    }
    mean /= iw.Size();
    for(size_t i = 0; i < mean_deviation.size(); ++i)
    {
        mean_deviation[i] = iw.GetIndices()[i] - mean;
    }
    auto min = *std::min_element(mean_deviation.begin(), mean_deviation.end()); // will be green
    min *= -1; // used to move the left bound to 0, instead of having an interval [a; b] with a != 0 (easier to deal with)
    auto max = *std::max_element(mean_deviation.begin(), mean_deviation.end()); // will be red
    max += min; // shift the right bound
    for(size_t i = 0; i < mean_deviation.size(); ++i)
    {
        mean_deviation[i] += min; // we have to shift (see comments above)
        auto normalized = max != 0 ? (int)((mean_deviation[i] / max) * 256 * 4) : 0;
        auto x = normalized % 256;
        int r = 0, g = 0, b = 0;
        // the idea is to do the following : blue -> cyan -> green -> yellow -> red -> blue
        switch(normalized / 256)
        {
            case 0 : // blue : rbg(0, 0, 255) -> cyan : rgb(0, 255, 255)
                r = 0;
                g = x;
                b = 255;
                break;
            case 1 : // cyan : rgb(0, 255, 255) -> green : rgb(0, 255, 0)
                r = 0;
                g = 255;
                b = 255 - x;
                break;
            case 2 : // green : rgb(0, 255, 0) -> yellow : rgb(255, 255, 0)
                r = x;
                g = 255;
                b = 0;
                break;
            case 3 : // yellow : rgb(255, 255, 0) -> red : rgb(255, 0, 0)
                r = 255;
                g = 255 - x;
                b = 0;
                break;
            case 4 : // red : rgb(255, 0, 0) -> blue : rgb(0, 0, 255)
                r = 255 - x;
                g = 0;
                b = x;
        }
        c[i] += std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
    }
    return c;
}

std::vector<double> GraphDrawer::AdaptRadius(IndicesWrapper iw)
{
    if(iw.Size() == 0)
        return {};
    auto min = *std::min_element(iw.GetIndices().begin(), iw.GetIndices().end());
    auto max = *std::max_element(iw.GetIndices().begin(), iw.GetIndices().end());
    std::vector<double> ar(iw.Size(), 0);
    double alpha = 0.0, beta = 0.0;
    if(min != max)
    {
        alpha = (MAX_RADIUS_MULT - MIN_RADIUS_MULT) / (max - min);
        beta = MIN_RADIUS_MULT - alpha * min;
    }
    for(int i = 0; i < iw.Size(); ++i)
    {
        if(min != max)
            ar[i] = alpha * iw.GetIndices()[i] + beta;
        else
            ar[i] = 1;
    }
    return ar;
}


void GraphDrawer::DrawShortestPath(Graph g, std::set<int> aretesVertes)
{
    double maximumX = std::numeric_limits<double>::min(), maximumY = std::numeric_limits<double>::min(), minimumX = std::numeric_limits<double>::max(), minimumY = std::numeric_limits<double>::max();
    bool test = false;
    m_rayon =  Closest(g.GetSommets());
    Svgfile svg(m_outputPath, m_width, m_height);

    for(auto s : g.GetSommets())
    {
        if(s.GetX() > maximumX)
            maximumX = s.GetX();
        if(s.GetX() < minimumX)
            minimumX = s.GetX();
        if(s.GetY() > maximumY)
            maximumY = s.GetY();
        if(s.GetY() < minimumY)
            minimumY = s.GetY();
    }

    double proportionalityX = ((m_width - 2*MARGE - m_rayon) * (1 / (maximumX-minimumX)));
    double proportionalityY = ((m_height - 2*MARGE - m_rayon) * (1 / (maximumY-minimumY)));
    double x1, y1, x2, y2, x3 = 0.0, y3 = 0.0, temp;

    double dec = (15 * m_height) / 6000;

    m_rayon = std::max(MIN_RADIUS, std::min(m_rayon * proportionalityX - 1, m_rayon * proportionalityY - 1));

    proportionalityX = ((m_width - 2*MARGE - 2*m_rayon) * (1 / (maximumX-minimumX)));
    proportionalityY = ((m_height - 2*MARGE - 2*m_rayon) * (1 / (maximumY-minimumY)));

    for(auto s : g.GetSommets())
    {
        svg.AddSommet(proportionalityX * (s.GetX() - minimumX) + MARGE, proportionalityY * (s.GetY() - minimumY) + MARGE,
                      m_rayon, "red", s.GetName(), s.GetId(), -1, true);
    }
    for(auto a : g.GetAretes())
    {
        if(g.GetDeleted().count(a.GetId())==0)
        {
            x1 = proportionalityX * (g.GetSommets()[a.GetOrigin()].GetX() - minimumX) + MARGE;
            y1 = proportionalityY * (g.GetSommets()[a.GetOrigin()].GetY() - minimumY) + MARGE;
            x2 = proportionalityX * (g.GetSommets()[a.GetTarget()].GetX() - minimumX) + MARGE;
            y2 = proportionalityY * (g.GetSommets()[a.GetTarget()].GetY() - minimumY) + MARGE;
            test = false;
            if(g.GetOriente())
            {
                for(auto b : g.GetSiblings(a.GetTarget()))
                {
                    if(b.second.GetId() == a.GetOrigin())
                    {
                        x3 = (x2 - x1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                        y3 = (y2 - y1) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                        test = true;

                        temp = x3;
                        x3 = y3;
                        y3 = -temp;
                    }
                }
            }
            if(!test)
            {
                if(aretesVertes.count(a.GetId())==0)
                    svg.AddArete(x1, y1, x2, y2, m_rayon, -1 ,"rgb(0, 0, 0)", 1, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId(), true);
                else
                    svg.AddArete(x1, y1, x2, y2, m_rayon, -1 , "green", 5, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId(), true);
            }
            else
                if(aretesVertes.count(a.GetId())==0)
                    svg.AddArete(x1 + x3*dec, y1 + y3*dec, x2 + x3*dec, y2 + y3*dec, m_rayon * cos( atan(dec / (double)m_rayon) ), -1, "rgb(0, 0, 0)", 1, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId());
                else
                    svg.AddArete(x1 + x3*dec, y1 + y3*dec, x2 + x3*dec, y2 + y3*dec, m_rayon * cos( atan(dec / (double)m_rayon) ), -1,  "green", 5, g.GetWeighted(), a.GetWeight(),g.GetOriente(), a.GetId());
        }
    }
}

double GraphDrawer::Closest(std::vector<Sommet> points)
{
    std::sort(points.begin(), points.end(), [](Sommet &lhs, Sommet &rhs) { return lhs.GetX() < rhs.GetX(); });
    return ClosestSorted(points) / 4;
}

double GraphDrawer::ClosestSorted(std::vector<Sommet> points)
{
    if(points.size() <= 3) // brute force is acceptable
        return BruteForce(points);
    int mid = (int)points.size() / 2; // dichotomy
    Sommet mid_point = points[mid];
    auto dist_left = ClosestSorted(std::vector<Sommet> (points.begin(), points.begin() + mid));
    auto dist_right = ClosestSorted(std::vector<Sommet> (points.begin() + mid, points.end()));

    double dist = Min(dist_left, dist_right);

    std::vector<Sommet> strip;
    int j = 0;
    for(size_t i = 0; i < points.size(); ++i)
    {
        if(std::abs(points[i].GetX() - mid_point.GetX()) < dist)
        {
            strip.push_back(points[i]);
            j++;
        }
    }
    return Min(dist, ClosestStrip(strip, dist));
}

double GraphDrawer::Min(double left, double right)
{
    return std::min(left, right);
}

double GraphDrawer::BruteForce(std::vector<Sommet> points)
{
    double min = 0;
    bool first = true;
    for(size_t i = 0; i < points.size(); ++i)
    {
        for(size_t j = i + 1; j < points.size(); ++j)
        {
          if(first)
          {
            min = Distance(points[i], points[j]);
            first = false;
          }
          else
          {
            auto temp = Distance(points[i], points[j]);
            if(temp < min)
              min = temp;
          }
        }
    }
    return min;
}

double GraphDrawer::Distance(Sommet a, Sommet b)
{
    return sqrt(pow(a.GetX() - b.GetX(), 2) + pow(a.GetY() - b.GetY(), 2));
}

double GraphDrawer::ClosestStrip(std::vector<Sommet> strip, double dist)
{
    auto min = dist;
    std::sort(strip.begin(), strip.end(), [](Sommet &lhs, Sommet &rhs) { return lhs.GetY() < rhs.GetY(); });
    for(size_t i = 0; i < strip.size(); ++i)
    {
        for(size_t j = i + 1; j < strip.size() && (strip[j].GetY() - strip[i].GetY()) < min; ++j)
        {
            auto temp = Distance(strip[i], strip[j]);
            if(temp < min)
                min = temp;
        }
    }
    return min;
}

GraphDrawer::~GraphDrawer()
{ }
