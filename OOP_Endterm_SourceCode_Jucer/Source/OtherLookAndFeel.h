/*
  ==============================================================================

    OtherLookAndFeel.h
    Author:  KJ1364

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once

//Source: https://www.youtube.com/watch?v=po46y8UKPOY&list=PLLgJJsrdwhPxa6-02-CeHW8ocwSwl2jnu&index=7
/**look and feel for rotary slider*/
class OtherLookAndFeel : public LookAndFeel_V4
{
    public:
   OtherLookAndFeel()
   {
   }
    //Source: https://www.youtube.com/watch?v=_IocXoXUWdQ
    /**draw custom rotary slider*/
    void drawRotarySlider(Graphics &g , int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
    {
        float diameter = jmin(width, height);
        float radius = diameter/2;
        float centreX = x + width/2;
        float centreY = y + height/2;
        float rx = centreX - radius;
        float ry = centreY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
        
        //parameters for dial area2
        float radius2 = (diameter - diameter/10) / 2;
        float rx2 = (centreX ) - (radius2);
        float ry2 = (centreY ) - radius2;
        
        Rectangle<float> dialArea (rx, ry,
                                   diameter, diameter);
        Rectangle<float> dialArea2 (rx2, ry2,
                                    diameter - diameter/10, diameter - diameter/10);
        
        //outer ellipse
        g.setColour(Colour::fromString("#BBC3CD"));
        g.fillEllipse(dialArea);
        
        //inner ellipse
        g.setColour(Colour::fromString("#E9E9E9"));
        g.fillEllipse(dialArea2);
        
        //ellipse to signal postion on slider
        g.setColour(Colour::fromString("#BBC3CD"));
        Path dialTick;
        dialTick.addEllipse(0, -radius ,
                            diameter/7,diameter/7);
        g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centreX, centreY));
    }
};

