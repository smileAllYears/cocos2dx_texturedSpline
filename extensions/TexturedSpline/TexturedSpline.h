#pragma once
#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

class CC_EX_DLL TexturedSpline : public cocos2d::Node, public cocos2d::TextureProtocol
{
public:

	enum class InterpolationType
	{
		CATMULL_ROM,
		B_CUBIC,
		LINEAR,
	};
	virtual ~TexturedSpline();
    
    static TexturedSpline* create(cocos2d::PointArray *config, float tension,  unsigned int segments, const cocos2d::Color4F &color, unsigned int subvisionLevel, const std::string& imagePath, InterpolationType type = InterpolationType::CATMULL_ROM);
    
    void setPath(cocos2d::PointArray *config, float tension,  unsigned int segments, bool is_build = true);
    
    void setPathColor(const cocos2d::Color4F &color);

	//static constructors
    bool init1(cocos2d::PointArray *config, float tension,  unsigned int segments, unsigned int subvisionLevel, const std::string& imagePath, const cocos2d::Color4F &color, InterpolationType type = InterpolationType::CATMULL_ROM);
    bool initWithTexture(cocos2d::PointArray *config, float tension,  unsigned int segmentsh, unsigned int subvisionLevel, cocos2d::Texture2D* texture, const cocos2d::Color4F &color, InterpolationType type = InterpolationType::CATMULL_ROM);

	//--Node--
	void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	//--TextureProtocol--
	virtual cocos2d::Texture2D* getTexture() const override;
	virtual void setTexture(cocos2d::Texture2D *texture) override;

	//--BlendProtocol--
	virtual void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override;
	virtual const cocos2d::BlendFunc& getBlendFunc() const override;

//	//--helper methods--
//	bool buildGeometry(std::vector<cocos2d::Vec2> path, unsigned int subvisionLevel);

	//--configuration--
	//scales the thickness of line and repeat rate
	CC_PROPERTY_PASS_BY_REF(float, m_strokeScale, StrokeScale);
	//true by default. The texture is repeated around the ring. Textures must be PoT for GL_REPEAT
	CC_PROPERTY_PASS_BY_REF(bool, m_isTextureRepeated, IsTextureRepeated);

CC_CONSTRUCTOR_ACCESS:
	TexturedSpline();
//	bool init1(std::vector<cocos2d::Vec2> path, unsigned int subvisionLevel, const std::string& imagePath, const cocos2d::Color4F &color, InterpolationType type = InterpolationType::CATMULL_ROM);
//	bool initWithTexture(std::vector<cocos2d::Vec2> path, unsigned int subvisionLevel, cocos2d::Texture2D* texture, const cocos2d::Color4F &color, InterpolationType type = InterpolationType::CATMULL_ROM);

	//texture
	cocos2d::Texture2D* m_texture;
	cocos2d::BlendFunc m_blendFunc;

	//geometry
	std::vector<cocos2d::Vec2> path;
	unsigned int m_subvisionLevel;
	std::vector<cocos2d::Vec2> m_vertices;
	std::vector<cocos2d::Tex2F> m_texCoords;
	
	//interpolation
	InterpolationType			m_interpolationType;
	std::vector<cocos2d::Vec2>	GetInterpolatedPath(unsigned int segments = 1) const;
	cocos2d::Vec2				GetInterpolation(float t, unsigned int pointNum) const;
	static cocos2d::Vec2		GetInterpolation(InterpolationType type, float t, cocos2d::Vec2 p0, cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3);

	//rendering
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
    
    cocos2d::Color4F _color;

private:
    //--helper methods--
    bool buildGeometry(std::vector<cocos2d::Vec2> path, unsigned int subvisionLevel);
    
	CC_DISALLOW_COPY_AND_ASSIGN(TexturedSpline);
};

NS_CC_EXT_END

